#include "GameScene.h"

using namespace KamataEngine;

// --- 行列の掛け算 ---
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
}

// --- スケール行列の作成 ---
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result = {0};
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1.0f;
	return result;
}

// --- 回転行列の作成 (XYZ順) ---
Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate) {
	// 各軸の回転行列を計算して合成する処理（省略版として結果のみ）
	// 本来は Sin, Cos を使って X, Y, Z それぞれ作り Multiply する
	Matrix4x4 rx = {1, 0, 0, 0, 0, cosf(rotate.x), sinf(rotate.x), 0, 0, -sinf(rotate.x), cosf(rotate.x), 0, 0, 0, 0, 1};
	Matrix4x4 ry = {cosf(rotate.y), 0, -sinf(rotate.y), 0, 0, 1, 0, 0, sinf(rotate.y), 0, cosf(rotate.y), 0, 0, 0, 0, 1};
	Matrix4x4 rz = {cosf(rotate.z), sinf(rotate.z), 0, 0, -sinf(rotate.z), cosf(rotate.z), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

	return Multiply(rx, Multiply(ry, rz));
}

// --- 平行移動行列の作成 ---
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result = {0};
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	return result;
}

// --- 【本題】アフィン変換行列の作成 ---
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 matScale = MakeScaleMatrix(scale);
	Matrix4x4 matRot = MakeRotateXYZMatrix(rotate);
	Matrix4x4 matTrans = MakeTranslateMatrix(translate);

	// S * R * T の順番で合成
	return Multiply(matScale, Multiply(matRot, matTrans));
}

void GameScene::Initialize() {
	// 3Dモデルデータの生成
	modelBlock_ = Model::Create();

	// 要素数
	const uint32_t kNumBlockVirtical = 10;
	const uint32_t kNumBlockHorizontal = 20;
	// ブロック1個分の幅
	const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;

	// 要素数を変更する
	// 列数を設定(縦方向のブロック数)
	worldTransformBlocks_.resize(kNumBlockVirtical);
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		// 列数を設定(横方向のブロック数)
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}

	// キューブの生成
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			worldTransformBlocks_[i][j] = new WorldTransform();
			worldTransformBlocks_[i][j]->Initialize();
			worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;
			worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * (i + 1) * 2.0f + (j % 2) * 2.0f;
		}
	}

	camera_.Initialize();

	// デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
}

void GameScene::Update() {

	// ブロックの更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;

			// アフィン変換行列の作成
			Matrix4x4 affineMatrix = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);

			// ワールド行列に代入
			worldTransformBlock->matWorld_ = affineMatrix;

			// 定数バッファに転送する
			worldTransformBlock->TransferMatrix();
		}
	}

	if (isDebugCameraActive_) {
		// デバックカメラの更新
		debugCamera_->Update();

		const Camera& debugCamera = debugCamera_->GetCamera();
		camera_.matView = debugCamera.matView;
		camera_.matProjection = debugCamera.matProjection;
		// ビュープロジェクション行列の転送
		camera_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		camera_.UpdateMatrix();
	}

#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		isDebugCameraActive_ = true;
	}
#endif
}

void GameScene::Draw() {

	Model::PreDraw();

	// ブロックの描画
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;

			modelBlock_->Draw(*worldTransformBlock, camera_);
		}
	}
	Model::PostDraw();
}

GameScene::~GameScene() {
	// 3Dモデルデータの解放
	delete modelBlock_;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();

	delete debugCamera_;
}
