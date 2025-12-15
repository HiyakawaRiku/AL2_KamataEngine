#pragma once
#include "KamataEngine.h"
#include "2d/ImGuiManager.h"

class GameScene {
public:
	void Initialize();

	void Update();

	void Draw();

	~GameScene();

private:
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//サウンドデータハンドル
	uint32_t soundDataHandle_ = 0;

	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;

	//3Dモデル
	KamataEngine::Model* model_ = nullptr;

	//ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransfrom_;

	//カメラ
	KamataEngine::Camera camera_;

	//音声再生ハンドル
	uint32_t voiceHandle_ = 0;

	//ImGuiで値を入力する変数
	float inputFloat[3] = {0, 0, 0};

	//デバックカメラ
	KamataEngine::DebugCamera* debagCamera_ = nullptr;
};
