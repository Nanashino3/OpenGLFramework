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

	// 乗算
	Quaternion operator*(const Quaternion& q) const
	{
		Quaternion temp;
		temp.mX = mW * q.mX + mX * q.mW + mZ * q.mY - mY * q.mZ;
		temp.mY = mW * q.mY + mY * q.mW + mX * q.mZ - mZ * q.mX;
		temp.mZ = mW * q.mZ + mZ * q.mW + mY * q.mX - mX * q.mY;
		temp.mW = mW * q.mW - mX * q.mX - mY * q.mY - mZ * q.mZ;
		return temp;
	}
	Quaternion& operator*=(const Quaternion &q)
	{
		*this = *this * q;
		return *this;
	}

	// 回転角と回転軸からクォータニオンを作成
	static Quaternion RotationAxis(const Vector3& axis, float rotate);
};