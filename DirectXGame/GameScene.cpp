#include "GameScene.h"
#include "MakeAffineFunction.h"

using namespace KamataEngine;

void GameScene::Initialize() {


mapChipField_ = new MapChipField;
// デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

		player_ = new Player();

		// 3Dモデルの生成
	model_ = Model::CreateFromOBJ("player", true);
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	modelBlock_ = Model::CreateFromOBJ("block", true);

	
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");
	GenerateBlocks();

	camera_ = new Camera();
	camera_->farZ = 800;
	camera_->Initialize();

	// 座標をマップチップ番号で指定
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(0, 19);
	player_->Initialize(model_, camera_, playerPosition);

	// 要素数
	const uint32_t kNumBlockVirtical = 10;
	const uint32_t kNumBlockHorizontal = 20;
	// ブロック1個分の幅
	const float kBlockWidth = 1.0f;
	const float kBlockHeight = 1.0f;

	// 要素数を変更する
	// 列数を設定(縦方向のブロック数)
	worldTransformBlocks_.resize(kNumBlockVirtical);
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		// 列数を設定(横方向のブロック数)
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}

	// ブロックの生成
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			worldTransformBlocks_[i][j] = new WorldTransform();
			worldTransformBlocks_[i][j]->Initialize();
			worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;
			worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * (i + 1) * 2.0f + (j % 2);
		}
	}


	// 天球の生成
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_, camera_);
}

void GameScene::Update() {

	skydome_->Update();

	// ブロックの更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

			if (!worldTransformBlock)
				continue;

			// アフィン変換行列の作成（各ブロックのSRTを使用）
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
		camera_->matView = debugCamera.matView;
		camera_->matProjection = debugCamera.matProjection;
		// ビュープロジェクション行列の転送
		camera_->TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		camera_->UpdateMatrix();
	}

	player_->Update();

#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		isDebugCameraActive_ = true;
	}
#endif
}

void GameScene::Draw() {
	Model::PreDraw();

	skydome_->Draw();

	// ブロックの描画
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;

			modelBlock_->Draw(*worldTransformBlock, *camera_);
		}
	}

	player_->Draw();

	Model::PostDraw();
}

GameScene::~GameScene() {
	delete modelSkydome_;
	delete modelBlock_;
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();

	delete model_;
	delete player_;
	delete debugCamera_;
	delete mapChipField_;

	delete skydome_;
}

void GameScene::GenerateBlocks() {
	// 要素数
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	// 要素数を変更する
	// 列数を設定(縦方向のブロック数)
	worldTransformBlocks_.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {

		// 1列の要素数を設定(横方向のブロック数)
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}

	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}