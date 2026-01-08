#include "Player.h"
#include "MakeAffineFunction.h"
#include <cassert>
#include <numbers>
#include<algorithm>

using namespace KamataEngine;

float EaseOut(float& t, float start, float end, float InitialVelocity) {

	float easeT = 1.0f - powf(1.0f - t, InitialVelocity);

	if (t >= 1.0f) {
		t = 1.0f;
	}

	return (1.0f - easeT) * start + easeT * end;
}

void Player::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position) {

	// NULLポインタチェック
	assert(model);

	model_ = model;
	camera_ = camera;

	worldTransform_.Initialize();
	// camera_->Initialize();

	// 初期回転の指定
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	// ワールド変換の初期化
	worldTransform_.Initialize();
	// camera_->Initialize();
	worldTransform_.translation_ = position;
}

void Player::Update() {

	// 移動入力
	// 左右移動入力
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {

		// 左右加速
		Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
			//左移動中の右入力
			if (velocity_.x < 0.0f) {
				//速度と逆方向に入力中は急ブレーキ
				velocity_.x *= (1.0f - kAttenuation);
			}

			acceleration.x += kAcceleration;

			if (lrDirection_ != LRDirection::kRight) {
				lrDirection_ = LRDirection::kRight;
			}
			turnFirstRotationY_ = worldTransform_.rotation_.y;
			turnTimer_ = kTimeTurn;
		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
			if (velocity_.x > 0.0f) {
				// 速度と逆方向に入力中は急ブレーキ
				velocity_.x *= (1.0f - kAttenuation);
			}

			acceleration.x -= kAcceleration;

			if (lrDirection_ != LRDirection::kLeft) {
				lrDirection_ = LRDirection::kLeft;
			}
			turnFirstRotationY_ = worldTransform_.rotation_.y;
			turnTimer_ = kTimeTurn;
		}

		//旋回制御
		if (turnTimer_>0.0f)
		{
			turnTimer_ -= 1.0f / 60.0f;

			//左右の自キャラ角度テーブル
			float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};
			//状態に応じた角度を取得する
			float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
			(void)destinationRotationY; // 変数未使用警告(C4189)を抑制
			//自キャラの角度を設定する
			worldTransform_.rotation_.y = EaseOut(turnTimer_,0.0f,1.0f,0.1f);

		}

		//加速/減速
		velocity_.x += acceleration.x;
		
		//最大速度制限
		velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

	} else {
		velocity_.x *= (1.0f - kAttenuation);
	}

	// 移動
	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;

	// 行列更新
	// アフィン変換行列の作成（各ブロックのSRTを使用）
	Matrix4x4 affineMatrix = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// ワールド行列に代入
	worldTransform_.matWorld_ = affineMatrix;

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
	
}

void Player::Draw() { model_->Draw(worldTransform_, *camera_); }