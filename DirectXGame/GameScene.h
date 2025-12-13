#pragma once
#include "KamataEngine.h"

class GameScene {
public:
	void Initialize();

	void Update();

	void Draw();

	~GameScene();

private:
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;
};
