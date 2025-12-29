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

	std::vector<KamataEngine::WorldTransform*> worldTransformBlocks_;
};
