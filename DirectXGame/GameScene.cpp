#include "GameScene.h"

using namespace KamataEngine;

void GameScene::Initialize() {
	textureHandle_ = TextureManager::Load("uvChecker.png");

	model_ = Model::Create();

	camera_ = new Camera();

	player_ = new Player();

	player_->Initialize(model_, textureHandle_,camera_ );
}

void GameScene::Update() { player_->Update(); }

void GameScene::Draw() { 
	
	Model::PreDraw();

	player_->Draw();

	Model::PostDraw();

}

GameScene::~GameScene() {

delete model_; 
delete player_;
}