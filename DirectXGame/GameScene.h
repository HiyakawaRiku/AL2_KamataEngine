#pragma once
#include "KamataEngine.h"
#include <vector>

class GameScene {
public:
	void Initialize();

	void Update();

	void Draw();
	~GameScene();

private:
	KamataEngine::Model* modelBlock_ = nullptr;
	KamataEngine::Camera camera_;

	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

	//デバックカメラ有効
	bool isDebugCameraActive_ = false;
	//デバックカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
};
