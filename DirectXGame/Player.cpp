#include "Player.h"
#include <cassert>
#include<numbers>
#include "MakeAffineFunction.h"

using namespace KamataEngine;

// --- 行列の掛け算 ---
//Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
//	Matrix4x4 result;
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++) {
//			result.m[i][j] = 0;
//			for (int k = 0; k < 4; k++) {
//				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
//			}
//		}
//	}
//	return result;
//}

//// --- スケール行列の作成 ---
//Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
//	Matrix4x4 result = {0};
//	result.m[0][0] = scale.x;
//	result.m[1][1] = scale.y;
//	result.m[2][2] = scale.z;
//	result.m[3][3] = 1.0f;
//	return result;
//}
//
//// --- 回転行列の作成 (XYZ順) ---
//Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate) {
//	// 各軸の回転行列を計算して合成する処理（省略版として結果のみ）
//	// 本来は Sin, Cos を使って X, Y, Z それぞれ作り Multiply する
//	Matrix4x4 rx = {1, 0, 0, 0, 0, cosf(rotate.x), sinf(rotate.x), 0, 0, -sinf(rotate.x), cosf(rotate.x), 0, 0, 0, 0, 1};
//	Matrix4x4 ry = {cosf(rotate.y), 0, -sinf(rotate.y), 0, 0, 1, 0, 0, sinf(rotate.y), 0, cosf(rotate.y), 0, 0, 0, 0, 1};
//	Matrix4x4 rz = {cosf(rotate.z), sinf(rotate.z), 0, 0, -sinf(rotate.z), cosf(rotate.z), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
//
//	return Multiply(rx, Multiply(ry, rz));
//}
//
//// --- 平行移動行列の作成 ---
//Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
//	Matrix4x4 result = {0};
//	result.m[0][0] = 1.0f;
//	result.m[1][1] = 1.0f;
//	result.m[2][2] = 1.0f;
//	result.m[3][3] = 1.0f;
//	result.m[3][0] = translate.x;
//	result.m[3][1] = translate.y;
//	result.m[3][2] = translate.z;
//	return result;
//}
//
//// --- 【本題】アフィン変換行列の作成 ---
//Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
//	Matrix4x4 matScale = MakeScaleMatrix(scale);
//	Matrix4x4 matRot = MakeRotateXYZMatrix(rotate);
//	Matrix4x4 matTrans = MakeTranslateMatrix(translate);
//
//	// S * R * T の順番で合成
//	return Multiply(matScale, Multiply(matRot, matTrans));
//}

void Player::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position) {

	// NULLポインタチェック
	assert(model);

	model_ = model;
	camera_ = camera;

	worldTransform_.Initialize();
	//camera_->Initialize();

	// 初期回転の指定
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	// ワールド変換の初期化
	worldTransform_.Initialize();
	//camera_->Initialize();
	worldTransform_.translation_ = position;
}

void Player::Update() {

	// アフィン変換行列の作成（各ブロックのSRTを使用）
	Matrix4x4 affineMatrix = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// ワールド行列に代入
	worldTransform_.matWorld_ = affineMatrix;

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Player::Draw() { model_->Draw(worldTransform_, *camera_); }