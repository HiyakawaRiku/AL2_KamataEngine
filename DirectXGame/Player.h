#pragma once
#include "KamataEngine.h"

class Player {

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHadle">テクスチャハンドル</param>
	void Initialize(KamataEngine::Model* model, uint32_t textureHadle, KamataEngine::Camera* camera);
	void Update();
	void Draw();

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model* model_=nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	KamataEngine::Camera* camera_;
};
