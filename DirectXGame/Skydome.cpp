#include "Skydome.h"

void Skydome::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera) {

	// NULLポインタチェック
	assert(model);

	worldTransform_.Initialize();
	model_ = model;
	camera_ = camera;
}
void Skydome::Update() { 
	worldTransform_.TransferMatrix(); }
void Skydome::Draw() {
	// KamataEngine::Model::PreDraw();
	// 3Dモデル描画
	model_->Draw(worldTransform_, *camera_);

	// KamataEngine::Model::PostDraw();
}