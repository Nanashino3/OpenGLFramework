#pragma once

namespace tkl
{
	const float PI = 3.14159265358979f;

	inline float ToRadian(float degree){ return degree * PI / 180.0f; }
	inline float ToDegree(float radian){ return radian * 180.0f / PI; }
}