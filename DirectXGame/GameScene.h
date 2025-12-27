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
	KamataEngine::Model* model_ = nullptr;
	std::vector<KamataEngine::WorldTransform*> worldTransformBlocks_;
};
