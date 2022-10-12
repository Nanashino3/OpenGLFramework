#pragma once
#include <algorithm>

class Vector3;
class Quaternion;
class Matrix
{
public:
	Matrix(){}

	const float& operator[](unsigned int i) const { return mMatrix[i]; }
	float& operator[](unsigned int i) { return mMatrix[i]; }

	static Matrix Identity()
	{
		Matrix temp;
		temp.LoadIdentity();
		return temp;
	}

	// 行列の配列を返す
	const float* GetData() const { return reinterpret_cast<const float*>(&mMatrix[0]); }
	Vector3 GetTranslation() const;

	// 乗算
	Matrix operator*(const Matrix& m) const
	{
		Matrix temp;
		for (int i = 0; i < 16; ++i) {
			const int j = i & 3;	// 0011
			const int k = i & ~3;	// 1100

			temp[i] = mMatrix[0  + j] * m[k + 0] +
					  mMatrix[4  + j] * m[k + 1] +
					  mMatrix[8  + j] * m[k + 2] +
					  mMatrix[12 + j] * m[k + 3];
		}

		return temp;
	}
	Matrix& operator*=(const Matrix& m)
	{
		*this = *this * m;
		return *this;
	}

	static Matrix CreateTranslation(const Vector3& pos);
	static Matrix CreateScale(const Vector3& scale);
	static Matrix CreateRotationFromQuaternion(const Quaternion& q);
	static Matrix CreatePerspectiveProjection(float angle, float aspect, float near, float far);
	static Matrix CreateLookAt(const Vector3& camPos, const Vector3& targetPos, const Vector3& upVector);

private:
	// 単位行列を設定
	void LoadIdentity()
	{
#if 1
		mMatrix[0]  = 1.0f; mMatrix[1]  = 0.0f; mMatrix[2]  = 0.0f; mMatrix[3]  = 0.0f;
		mMatrix[4]  = 0.0f; mMatrix[5]  = 1.0f; mMatrix[6]  = 0.0f; mMatrix[7]  = 0.0f;
		mMatrix[8]  = 0.0f; mMatrix[9]  = 0.0f; mMatrix[10] = 1.0f; mMatrix[11] = 0.0f;
		mMatrix[12] = 0.0f; mMatrix[13] = 0.0f; mMatrix[14] = 0.0f; mMatrix[15] = 1.0f;
#else
		std::fill(mMatrix, mMatrix + 16, 0.0f);
		mMatrix[0] = mMatrix[5] = mMatrix[10] = mMatrix[15] = 1.0f;
#endif
	}

private:
	float mMatrix[16];
};