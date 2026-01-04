#pragma once
#include "KamataEngine.h"
#include "MapChipField.h"
#include <vector>

class GameScene {
public:
	void Initialize();
	void Update();
	void Draw();
	~GameScene();

	void GenerateBlocks();

private:
	//マップチップフィールド
	MapChipField* mapChipField_;
};
