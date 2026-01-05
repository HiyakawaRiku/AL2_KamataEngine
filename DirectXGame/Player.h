#pragma once
#include "KamataEngine.h"

class Player {

public:
	/// <summary>
	/// しょｋ
	/// </summary>
	/// <param name="model"></param>
	/// <param name="textureHadle"></param>
	/// <param name="camera"></param>
	void Initialize(KamataEngine::Model* model, uint32_t textureHadle, KamataEngine::Camera* camera);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
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
