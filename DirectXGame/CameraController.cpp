#define NOMINMAX
#include <algorithm>
#include "CameraController.h"
#include "cassert"

using namespace KamataEngine;
using namespace MathUtility;

void CameraController::Initialize() {

	// カメラの初期化
	assert(camera_);
	camera_ = new Camera;
	camera_->Initialize();
}

void CameraController::Update() { SetMoveableArea(); }

void CameraController::Reset() {

	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	// 追従対象とオフセットと追従対象の速度から目標座標を計
	targetCoordinates = targetWorldTransform.translation_ + targetOffset_+targetVelocity*kVelocityBias;

	//座標補間によりゆったり追従
	camera_->translation_ = Lerp(camera_->translation_, targetCoordinates, kInterpolationRate);

	//追従対象が画面外にでないように補正
	camera_->translation_.x = std::max(camera_->translation_.x, targetVelocity + margin_.left);
	camera_->translation_.x = std::min(camera_->translation_.x, targetVelocity + margin_.right);
	camera_->translation_.y = std::max(camera_->translation_.y, targetVelocity + margin_.bottom);
	camera_->translation_.y = std::min(camera_->translation_.y, targetVelocity + margin_.top);

	//移動範囲制限
	camera_->translation_.x = std::max(camera_->translation_.x, movableArea_.left);
	camera_->translation_.x = std::max(camera_->translation_.x, movableArea_.right);
	camera_->translation_.y = std::max(camera_->translation_.y, movableArea_.bottom);
	camera_->translation_.y = std::max(camera_->translation_.y, movableArea_.top);

	// 行列を更新する
	camera_->UpdateMatrix();
}