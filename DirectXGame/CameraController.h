#pragma once
#include "KamataEngine.h"


struct Rect {
	float left = 0.0f;   // 左端
	float right = 1.0f;  // 右端
	float bottom = 0.0f; // 下端
	float top = 1.0f;    // 上端
};

// 前方宣言
class Player;

class CameraController {
public:
	void Initialize();
	void Update(KamataEngine::Camera &camera);
	void SetTarget(Player* target) { target_ = target; }
	void Reset();
	void SetMoveableArea(Rect const& area) { movableArea_ = area; }

	private:

		//カメラ
	    KamataEngine::Camera camera_;
	    Player* target_ = nullptr;

	    KamataEngine::Vector3 targetOffset_ = {0, 0, -15.0f};

		//カメラ移動範囲
	    Rect movableArea_ = {0, 100, 0, 100};
	    //カメラの目標座標
	    KamataEngine::Vector3 targetCoordinates;
		//座標補間割合
	    static inline const float kInterpolationRate = 0.1f;

		//速度掛け率
	    static inline const float kVelocityBias = 25.0f;

		//追従対象の各方向へのカメラ移動範囲
	    static inline const Rect margin_ = {-20,20,12,-12};
};
