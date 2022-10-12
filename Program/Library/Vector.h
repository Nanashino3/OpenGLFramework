#pragma once

class Quaternion;
class Vector3
{
public:
	float mX, mY, mZ;

	Vector3() : mX(0), mY(0), mZ(0){}
	Vector3(float x, float y, float z) : mX(x), mY(y), mZ(z){}

	friend Vector3 operator+(const Vector3& a, const Vector3& b){
		return Vector3(a.mX + b.mX, a.mY + b.mY, a.mZ + b.mZ);
	}
	friend Vector3 operator-(const Vector3& a, const Vector3& b){
		return Vector3(a.mX - b.mX, a.mY - b.mY, a.mZ - b.mZ);
	}
	friend Vector3 operator*(const Vector3& v, float scalar)
	{
		return Vector3(v.mX * scalar, v.mY * scalar, v.mZ * scalar);
	}

	// ベクトルの配列を返す
	const float* GetData() const { return reinterpret_cast<const float*>(&mX); }

	// ベクトルの外積
	static Vector3 Cross(const Vector3& v1, const Vector3& v2)
	{
		Vector3 temp;
		temp.mX = v1.mY * v2.mZ - v1.mZ * v2.mY;
		temp.mY = v1.mZ * v2.mX - v1.mX * v2.mZ;
		temp.mZ = v1.mX * v2.mY - v1.mY * v2.mX;
		return temp;
	}

	// ベクトルの内積
	static float Dot(const Vector3& v1, const Vector3& v2)
	{
		return v1.mX * v2.mX + v1.mY * v2.mY + v1.mZ * v2.mZ;
	}

	static Vector3 Normalize(const Vector3& v);
	static Vector3 TransformCoord(const Vector3& v, const Quaternion& q);

	static const Vector3 ZERO;
	static const Vector3 UNITX;
	static const Vector3 UNITY;
	static const Vector3 UNITZ;
	static const Vector3 NEG_UNITX;
	static const Vector3 NEG_UNITY;
	static const Vector3 NEG_UNITZ;
};