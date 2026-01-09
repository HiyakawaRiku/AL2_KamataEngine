#define NOMINMAX
#include <algorithm>
#include "CameraController.h"
#include "cassert"
#include"Player.h"

using namespace KamataEngine;
using namespace MathUtility;

void CameraController::Initialize() {

	//// カメラの初期化
	//assert(camera_);
	/*camera_ = new Camera;*/
	camera_.Initialize();
}

void CameraController::Update(Camera& camera) {
	
	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	const Vector3& targetVelocity = target_->GetVelocity();
	// 追従対象とオフセットと追従対象の速度から目標座標を計
	targetCoordinates = targetWorldTransform.translation_ + targetOffset_ +targetVelocity*kVelocityBias;

	//座標補間によりゆったり追従
	 camera_.translation_.x = Lerp(camera_.translation_.x, targetCoordinates.x, kInterpolationRate);
	 camera_.translation_.y = Lerp(camera_.translation_.y, targetCoordinates.y, kInterpolationRate);
	 camera_.translation_.z = Lerp(camera_.translation_.z, targetCoordinates.z, kInterpolationRate);
	//追従対象が画面外にでないように補正
	 camera_.translation_.x = std::max(camera_.translation_.x, targetVelocity.x + margin_.left);
	 camera_.translation_.x = std::min(camera_.translation_.x, targetVelocity.x + margin_.right);
	 camera_.translation_.y = std::max(camera_.translation_.y, targetVelocity.y + margin_.bottom);
	 camera_.translation_.y = std::min(camera_.translation_.y, targetVelocity.y + margin_.top);

	//移動範囲制限
	 camera_.translation_.x = std::max(camera_.translation_.x, movableArea_.left);
	 camera_.translation_.x = std::min(camera_.translation_.x, movableArea_.right);
	 camera_.translation_.y = std::max(camera_.translation_.y, movableArea_.bottom);
	 camera_.translation_.y = std::min(camera_.translation_.y, movableArea_.top);

	camera_.UpdateMatrix();

	// 行列を更新する
	camera.matView = camera_.matView;
	camera.matProjection = camera_.matProjection;
	// ビュープロジェクション行列の転送
	camera.TransferMatrix();

	/*SetMoveableArea(); */}

void CameraController::Reset() {

	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	// 追従対象とオフセットと追従対象の速度から目標座標を計
	// targetCoordinates = targetWorldTransform.translation_ + targetOffset_ /*+targetVelocity*kVelocityBias*/;
	camera_.translation_ = targetWorldTransform.translation_ + targetOffset_ /*+targetVelocity*kVelocityBias*/;
}