#pragma once

namespace tkl
{
class Matrix;
class Quaternion;
class Vector3
{
public:
	union{
		struct{
			float mX, mY, mZ;
		};
		float mVec[3];
	};

	Vector3() : mX(0), mY(0), mZ(0){}
	Vector3(float x, float y, float z) : mX(x), mY(y), mZ(z){}

	Vector3 operator+(const Vector3& a) const;
	Vector3& operator+=(const Vector3& a);
	Vector3 operator-(const Vector3& a) const;
	Vector3& operator-=(const Vector3& a);

	Vector3 operator+(float s) const;
	Vector3& operator+=(float s);
	Vector3 operator-(float s) const;
	Vector3& operator-=(float s);
	Vector3 operator*(float s) const;
	Vector3& operator*=(float s);

	// ベクトルの配列を返す
	float* GetData() const { return (float*)(&mVec[0]); }

	static Vector3 Cross(const Vector3& v1, const Vector3& v2);
	static float Dot(const Vector3& v1, const Vector3& v2);
	static Vector3 Normalize(const Vector3& v);
	static Vector3 TransformCoord(const Vector3& v, const Quaternion& q);
	static Vector3 TransformCoord(const Vector3& v, const Matrix& m);
	static Vector3 CreateScreenRay(int screenX, int screenY, int screenW, int screenH, const tkl::Matrix& view, const tkl::Matrix& projection);

	static const Vector3 ZERO;
	static const Vector3 UNITX;
	static const Vector3 UNITY;
	static const Vector3 UNITZ;
	static const Vector3 NEG_UNITX;
	static const Vector3 NEG_UNITY;
	static const Vector3 NEG_UNITZ;
};

} // namespace tkl