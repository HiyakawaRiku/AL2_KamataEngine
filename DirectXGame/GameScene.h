#pragma once
#include "KamataEngine.h"
#include "Player.h"

class GameScene {
public:
	void Initialize();

	void Update();

	void Draw();

	~GameScene();

private:
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//3Dモデル
	KamataEngine::Model* model_ = nullptr;

	//デバックカメラ
	KamataEngine::Camera* camera_ = nullptr;

	Player* player_ = nullptr;
};
