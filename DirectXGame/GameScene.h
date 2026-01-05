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

	//3Dモデルデータ
	KamataEngine::Model* model_ = nullptr;

	//カメラ
	KamataEngine::Camera* camera_ = nullptr;

	//自キャラ
	Player* player_ = nullptr;
};
