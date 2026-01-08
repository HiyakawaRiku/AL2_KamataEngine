#pragma once
#include "KamataEngine.h"
#include <vector>
#include "MapChipField.h"
#include"Skydome.h"
#include "Player.h"

class GameScene {
public:
	void Initialize();

	void Update();

	void Draw();
	~GameScene();
	void GenerateBlocks();

	private:
	// マップチップフィールド
	MapChipField* mapChipField_;

	// 天球
	Skydome* skydome_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// 3Dモデル
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* modelBlock_ = nullptr;
	KamataEngine::Model* modelSkydome_ = nullptr;
	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

	// デバックカメラ有効
	bool isDebugCameraActive_ = false;
	// デバックカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	Player* player_ = nullptr;
};
