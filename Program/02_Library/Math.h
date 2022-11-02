#pragma once

#include "Vector.h"
namespace tkl
{
	const float PI = 3.14159265358979f;

	inline float ToRadian(float degree){ return degree * PI / 180.0f; }
	inline float ToDegree(float radian){ return radian * 180.0f / PI; }

	//********************************************************************************
	// name... GetSidesPointAndPlane
	// work... �w����W�����ʂ̕\���ǂ���ɑ��݂��邩���肷��
	// arg1... �w����W
	// arg2... ���ʂ̖@��
	// arg3... ���ʏ�ɑ��݂���ǂ����̍��W
	// ret.... �\...1 	��...-1		���ʏ�...0
	// tips... none
	int GetSidesPointAndPlane(const Vector3& v, const Vector3& pn, const Vector3& pv);
}