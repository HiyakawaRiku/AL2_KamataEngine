#include "GameScene.h"

using namespace KamataEngine;

void GameScene::Initialize() {
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("tex1.png");

	// サウンドデータの読み込み
	soundDataHandle_ = Audio::GetInstance()->LoadWave("mokugyo.wav");

	// 音声再生
	Audio::GetInstance()->PlayWave(soundDataHandle_);

	voiceHandle_ = Audio::GetInstance()->PlayWave(soundDataHandle_, true);

	// スプライトインスタンスを生成
	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	// 3Dモデルの生成
	model_ = Model::Create();

	// ワールドトランスフォームの初期化
	worldTransfrom_.Initialize();

	// カメラの初期化
	camera_.Initialize();

	//ライン描画が参照するカメラを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetCamera(&camera_);

	//デバックカメラの生成
	debagCamera_ = new DebugCamera(1280, 720);
}

void GameScene::Update() {

	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		Audio::GetInstance()->StopWave(voiceHandle_);
	}

	// スプライトの今の座標を取得
	Vector2 position = sprite_->GetPosition();

	// 座標を{ 2 , 1 }移動
	position.x += 2.0f;
	position.y += 1.0f;

	// 移動した座標をスプライトに反映
	sprite_->SetPosition(position);

	//デバックカメラの更新
	debagCamera_->Update();

	#ifdef _DEBUG
	ImGui::Begin("Debug1");
	ImGui::Text("Kamata Tarou %d.%d.%d", 2050, 12, 31);
	ImGui::InputFloat3("InputFloat3", inputFloat);
	ImGui::SliderFloat3("SliderFloat3", inputFloat, 0.0f, 1.0f);
	ImGui::ShowDemoWindow();
	ImGui::End();
#endif // _DEBUG
}

void GameScene::Draw() {

	// スプライト描画前処理
	Sprite::PreDraw();

	sprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

	// 3Dモデル描画前処理
	Model::PreDraw();

	// ３Dモデル描画
	model_->Draw(worldTransfrom_, camera_, textureHandle_);

	// 3Dモデル描画後処理
	Model::PostDraw();

	// ラインを描画する
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});

	model_->Draw(worldTransfrom_, debagCamera_->GetCamera(), textureHandle_);
}

GameScene::~GameScene() {
	delete sprite_;
	delete model_;
	delete debagCamera_;
}