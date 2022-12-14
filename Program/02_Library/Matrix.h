//****************************************************************************
// ファイル名：Matrix(行列クラス)
// 作　成　日：2022/10/7
#ifndef _MATRIX_H_
#define _MATRIX_H_
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

	//***************************************************************************
	// Matrix同士の乗算
	Matrix operator*(const Matrix& m) const;
	Matrix& operator*=(const Matrix& m);
	//***************************************************************************

	// 行列の配列を返す
	float* GetData() const { return (float*)&mMatrix[0]; }

	// 単位行列を作成
	static Matrix CreateIdentity();
	// 平行行列を作成
	static Matrix CreateTranslation(const Vector3& pos);
	// 拡縮行列を作成
	static Matrix CreateScale(const Vector3& scale);
	// クォータニオンから行列を作成
	static Matrix CreateRotationFromQuaternion(const Quaternion& q);
	// 透視射影行列を作成
	static Matrix CreatePerspectiveProjection(float angle, float aspect, float near, float far);
	// 正射影行列を作成
	static Matrix CreateOrthogonalProjection(float left, float right, float bottom, float top, float near, float far);
	// 視線行列を作成
	static Matrix CreateLookAt(const Vector3& camPos, const Vector3& targetPos, const Vector3& upVector);
	// ビューポート行列を作成
	static Matrix CreateViewport(int screenWidth, int screenHeight);
	// 逆行列を作成
	static Matrix CreateInverseMatrix(const Matrix& m);

private:
	// 単位行列を設定
	void LoadIdentity();
};

} // namespace tkl

#endif