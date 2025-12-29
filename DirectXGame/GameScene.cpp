#include "GameScene.h"

using namespace KamataEngine;

void GameScene::Initialize() {
	modelBlock_ = Model::Create();

	const uint32_t kNumBlockHorizontal = 20;
	const float kBlockWidth = 2.0f;
	worldTransformBlocks_.resize(kNumBlockHorizontal);
	camera_.Initialize();

	for (uint32_t i = 0; i < kNumBlockHorizontal; i++) {
		worldTransformBlocks_[i] = new WorldTransform();
		worldTransformBlocks_[i]->Initialize();
		worldTransformBlocks_[i]->translation_.x = kBlockWidth * i;
		worldTransformBlocks_[i]->translation_.y = 0.0f;
	}
}

void GameScene::Update() {
	for (WorldTransform* worldTransformBlock : worldTransformBlocks_) {

		worldTransformBlock->TransferMatrix();
	}
}

void GameScene::Draw() {

	Model::PreDraw();

	for (WorldTransform* worldTransformBlock : worldTransformBlocks_) {
		modelBlock_->Draw(*worldTransformBlock, camera_);
	}
	Model::PostDraw();
}

GameScene::~GameScene() {
	delete modelBlock_;
	for (WorldTransform* worldTransformBlock : worldTransformBlocks_) {
		delete worldTransformBlock;
	}
	worldTransformBlocks_.clear();
}
