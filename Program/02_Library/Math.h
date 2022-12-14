//****************************************************************************
// ファイル名：Math(計算)
// 作　成　日：2022/10/6
#ifndef _MATH_H_
#define _MATH_H_

#include "Vector.h"
namespace tkl
{
	const float PI = 3.14159265358979f;

	// ラジアン変換
	inline float ToRadian(float degree){ return degree * PI / 180.0f; }
	// 度数変換
	inline float ToDegree(float radian){ return radian * 180.0f / PI; }

	//********************************************************************************
	// name... GetSidesPointAndPlane
	// work... 指定座標が平面の表裏どちらに存在するか判定する
	// arg1... 指定座標
	// arg2... 平面の法線
	// arg3... 平面上に存在するどこかの座標
	// ret.... 表...1 	裏...-1		平面上...0
	// tips... none
	int GetSidesPointAndPlane(const Vector3& v, const Vector3& pn, const Vector3& pv);
}

#endif/