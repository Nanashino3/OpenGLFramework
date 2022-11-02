#pragma once
#include <algorithm>

namespace tkl
{
class Vector3;
class Quaternion;
class Matrix
{
public:
	union {
		struct {
			float _11, _21, _31, _41;
			float _12, _22, _32, _42;
			float _13, _23, _33, _43;
			float _14, _24, _34, _44;
		};
		float mMatrix[16];
	};

	Matrix();
	~Matrix();

	const float& operator[](unsigned int i) const { return mMatrix[i]; }
	float& operator[](unsigned int i) { return mMatrix[i]; }

	Matrix operator*(const Matrix& m) const;
	Matrix& operator*=(const Matrix& m);

	// çsóÒÇÃîzóÒÇï‘Ç∑
	float* GetData() const { return (float*)&mMatrix[0]; }

	static Matrix CreateIdentity();
	static Matrix CreateTranslation(const Vector3& pos);
	static Matrix CreateScale(const Vector3& scale);
	static Matrix CreateRotationFromQuaternion(const Quaternion& q);
	static Matrix CreatePerspectiveProjection(float angle, float aspect, float near, float far);
	static Matrix CreateOrthogonalProjection(float left, float right, float bottom, float top, float near, float far);
	static Matrix CreateLookAt(const Vector3& camPos, const Vector3& targetPos, const Vector3& upVector);
	static Matrix CreateViewport(int screenWidth, int screenHeight);
	static Matrix CreateInverseMatrix(const Matrix& m);

private:
	void LoadIdentity();
};

} // namespace tkl
