#pragma once
#include "KamataEngine.h"

/// <summary>
/// 天球
/// </summary>
class Skydome {

public:
	void Initialize(KamataEngine::Model* model,KamataEngine::Camera* camera);
	void Update();
	void Draw();

private:
	//ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	//モデル
	KamataEngine::Model* model_ = nullptr;

	// カメラ
	KamataEngine::Camera* camera_;
};