#pragma once

class Vector3;
class Quaternion
{
public:
	float mX, mY, mZ, mW;

	Quaternion()
	: mX(0.0), mY(0.0f), mZ(0.0f), mW(1.0f)
	{}

	Quaternion(float x, float y, float z, float w)
	: mX(x), mY(y), mZ(z), mW(w)
	{}

	// ��]�p�Ɖ�]������N�H�[�^�j�I�����쐬
	static Quaternion RotationAxis(const Vector3& axis, float rotate);
};