#include "GameScene.h"

using namespace KamataEngine;

void GameScene::Initialize() {
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("tex1.png");

	// スプライトインスタンスを生成
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
}

void GameScene::Update() {
//スプライトの今の座標を取得
	Vector2 position = sprite_->GetPosition();

	//座標を{ 2 , 1 }移動
	position.x += 2.0f;
	position.y += 1.0f;

	//移動した座標をスプライトに反映
	sprite_->SetPosition(position);
}

void GameScene::Draw() { 

	//スプライト描画前処理
	Sprite::PreDraw();

	sprite_->Draw();

	//スプライト描画後処理
	Sprite::PostDraw();
}

GameScene::~GameScene() { 
	delete sprite_;
}