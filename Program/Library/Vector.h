#pragma once

class Vector3
{
public:
	float mX, mY, mZ;

	Vector3() : mX(0), mY(0), mZ(0){}
	Vector3(float x, float y, float z) : mX(x), mY(y), mZ(z){}

//	Vector3 TransformCoord(const Vector3& v, const Quaternion& q);

	static const Vector3 ZERO;
	static const Vector3 UNITX;
	static const Vector3 UNITY;
	static const Vector3 UNITZ;
};