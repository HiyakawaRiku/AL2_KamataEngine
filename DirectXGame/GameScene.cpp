#include "GameScene.h"

using namespace KamataEngine;

void GameScene::Initialize() {
	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/Block.csv");
	GenerateBlocks();
}

void GameScene::Update() {}

void GameScene::Draw() {}

GameScene::~GameScene() { delete mapChipField_; }

void GameScene::GenerateBlocks() { 
	//要素数
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	//要素数を変更する
	//列数を設定(縦方向のブロック数)
	worldTransformBlocks_.resize();
	for (uint32_t i = 0; i < ; ++i) {
	
	//1列の要素数を設定(横方向のブロック数)
		worldTransformBlocks_[i].resize();
	}
}
