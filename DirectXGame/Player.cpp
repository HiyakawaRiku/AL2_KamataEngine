#include "Player.h"
#include <cassert>

void Player::Initialize(KamataEngine::Model* model, uint32_t textureHadle, KamataEngine::Camera* camera) {

	// NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = textureHadle;
	camera_ = camera;

	worldTransform_.Initialize();
	camera_->Initialize();
}

void Player::Update() {
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Player::Draw() { model_->Draw(worldTransform_, *camera_, textureHandle_); }