#include "Player.h"
#include<numbers>

void Player::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3 position) {
	//ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	//初期回転の指定
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
}
