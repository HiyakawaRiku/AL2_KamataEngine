#pragma once

#include "KamataEngine.h"

using Matrix4x4 = KamataEngine::Matrix4x4;
using Vector3 = KamataEngine::Vector3;

inline Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

// --- スケール行列の作成 ---
inline Matrix4x4 MakeScaleMatrix(const Vector3& scale);

// --- 回転行列の作成 (XYZ順) ---
inline Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate);
// --- 平行移動行列の作成 ---
inline Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

// --- 【本題】アフィン変換行列の作成 ---
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);