//****************************************************************************
// ファイル名：Matrix(行列クラス)
// 作　成　日：2022/10/7
#include "Matrix.h"

#include <cmath>
#include "Vector.h"
#include "Quaternion.h"
#include "Math.h"

namespace tkl
{
Matrix::Matrix()
: _11(1.0f), _12(0.0f), _13(0.0f), _14(0.0f)
, _21(0.0f), _22(1.0f), _23(0.0f), _24(0.0f)
, _31(0.0f), _32(0.0f), _33(1.0f), _34(0.0f)
, _41(0.0f), _42(0.0f), _43(0.0f), _44(1.0f)
{}

Matrix::~Matrix()
{}

//***************************************************************************
// Matrix同士の乗算
Matrix Matrix::operator*(const Matrix& m) const
{
	Matrix temp;
	temp.LoadIdentity();

	temp._11 = (_11 * m._11) + (_12 * m._21) + (_13 * m._31) + (_14 * m._41);
	temp._21 = (_21 * m._11) + (_22 * m._21) + (_23 * m._31) + (_24 * m._41);
	temp._31 = (_31 * m._11) + (_32 * m._21) + (_33 * m._31) + (_34 * m._41);
	temp._41 = (_41 * m._11) + (_42 * m._21) + (_43 * m._31) + (_44 * m._41);

	temp._12 = (_11 * m._12) + (_12 * m._22) + (_13 * m._32) + (_14 * m._42);
	temp._22 = (_21 * m._12) + (_22 * m._22) + (_23 * m._32) + (_24 * m._42);
	temp._32 = (_31 * m._12) + (_32 * m._22) + (_33 * m._32) + (_34 * m._42);
	temp._42 = (_41 * m._12) + (_42 * m._22) + (_43 * m._32) + (_44 * m._42);

	temp._13 = (_11 * m._13) + (_12 * m._23) + (_13 * m._33) + (_14 * m._43);
	temp._23 = (_21 * m._13) + (_22 * m._23) + (_23 * m._33) + (_24 * m._43);
	temp._33 = (_31 * m._13) + (_32 * m._23) + (_33 * m._33) + (_34 * m._43);
	temp._43 = (_41 * m._13) + (_42 * m._23) + (_43 * m._33) + (_44 * m._43);

	temp._14 = (_11 * m._14) + (_12 * m._24) + (_13 * m._34) + (_14 * m._44);
	temp._24 = (_21 * m._14) + (_22 * m._24) + (_23 * m._34) + (_24 * m._44);
	temp._34 = (_31 * m._14) + (_32 * m._24) + (_33 * m._34) + (_34 * m._44);
	temp._44 = (_41 * m._14) + (_42 * m._24) + (_43 * m._34) + (_44 * m._44);

	return temp;
}
Matrix& Matrix::operator*=(const Matrix& m)
{
	*this = *this * m;
	return *this;
}
//***************************************************************************

// 単位行列作成
Matrix Matrix::CreateIdentity()
{
	Matrix temp;
	temp.LoadIdentity();
	return temp;
}

// 平行行列を作成
Matrix Matrix::CreateTranslation(const Vector3& pos)
{
	Matrix temp;
	temp.LoadIdentity();
	temp._14 = pos.mX;
	temp._24 = pos.mY;
	temp._34 = pos.mZ;
	return temp;
}

// 拡縮行列を作成
Matrix Matrix::CreateScale(const Vector3& scale)
{
	Matrix temp;
	temp.LoadIdentity();
	temp._11 = scale.mX;
	temp._22 = scale.mY;
	temp._33 = scale.mZ;
	return temp;
}

// クォータニオンから行列を作成
Matrix Matrix::CreateRotationFromQuaternion(const Quaternion& q)
{
	Matrix temp;
	temp.LoadIdentity();
	temp._11 = 1.0f - 2.0f * q.mY * q.mY - 2.0f * q.mZ * q.mZ;
	temp._12 = 2.0f * q.mX * q.mY + 2.0f * q.mW * q.mZ;
	temp._13 = 2.0f * q.mX * q.mZ - 2.0f * q.mW * q.mY;
	temp._21 = 2.0f * q.mX * q.mY - 2.0f * q.mW * q.mZ;
	temp._22 = 1.0f - 2.0f * q.mX * q.mX - 2.0f * q.mZ * q.mZ;
	temp._23 = 2.0f * q.mY * q.mZ + 2.0f * q.mW * q.mX;
	temp._31 = 2.0f * q.mX * q.mZ + 2.0f * q.mW * q.mY;
	temp._32 = 2.0f * q.mY * q.mZ - 2.0f * q.mW * q.mX;
	temp._33 = 1.0f - 2.0f * q.mX * q.mX - 2.0f * q.mY * q.mY;
	return temp;
}

// 透視射影行列を作成
Matrix Matrix::CreatePerspectiveProjection(float angle, float aspect, float near, float far)
{
	Matrix temp;
	temp.LoadIdentity();
	float fovy = tkl::ToRadian(angle);

	float yScale = 1.0f / tanf(fovy * 0.5f);
	float xScale = yScale / aspect;

	temp._11 = xScale;
	temp._22 = yScale;
	temp._33 = -(far + near) / (far - near);
	temp._34 = -2.0f * far * near / (far - near);
	temp._43 = -1.0f;
	temp._44 = 0.0f;

	return temp;
}

// 正射影行列を作成
Matrix Matrix::CreateOrthogonalProjection(float left, float right, float bottom, float top, float near, float far)
{
	Matrix temp;
	temp.LoadIdentity();

	float ral = right + left;	// right add left
	float rsl = right - left;	// right subtraction left
	float tab = top + bottom;	// top add bottom
	float tsb = top - bottom;	// top subtraction bottom
	float fan = far + near;		// far add near
	float fsn = far - near;		// far subtraction near

	temp._11 = 2.0f / rsl;
	temp._14 = -ral / rsl;
	temp._22 = 2.0f / tsb;
	temp._24 = -tab / tsb;
	temp._33 = -2.0f / fsn;
	temp._34 = -fan / fsn;

	return temp;
}

// 視線行列を作成
Matrix Matrix::CreateLookAt(const Vector3& camPos, const Vector3& targetPos, const Vector3& upVector)
{
	Vector3 zAxis = Vector3::Normalize(camPos - targetPos);
	Vector3 xAxis = Vector3::Normalize(Vector3::Cross(upVector, zAxis));
	Vector3 yAxis = Vector3::Normalize(Vector3::Cross(zAxis, xAxis));

	Vector3 trans;
	trans.mX = -Vector3::Dot(xAxis, camPos);
	trans.mY = -Vector3::Dot(yAxis, camPos);
	trans.mZ = -Vector3::Dot(zAxis, camPos);

	Matrix temp;
	temp.LoadIdentity();

	temp._11 = xAxis.mX; temp._12 = xAxis.mY; temp._13 = xAxis.mZ; temp._14 = trans.mX;
	temp._21 = yAxis.mX; temp._22 = yAxis.mY; temp._23 = yAxis.mZ; temp._24 = trans.mY;
	temp._31 = zAxis.mX; temp._32 = zAxis.mY; temp._33 = zAxis.mZ; temp._34 = trans.mZ;

	return temp;
}

// ビューポート行列を作成
Matrix Matrix::CreateViewport(int screenWidth, int screenHeight)
{
	Matrix temp;
	temp.LoadIdentity();
	temp._11 = static_cast<float>(screenWidth >> 1);
	temp._14 = static_cast<float>(screenWidth >> 1);
	temp._22 = static_cast<float>(screenHeight >> 1) * -1.0f;
	temp._24 = static_cast<float>(screenHeight >> 1);
	temp._33 = 1.0f;
	return temp;
}

// 逆行列を作成(TODO：何やってるかはわかってない)
Matrix Matrix::CreateInverseMatrix(const Matrix& m)
{
	Matrix temp;
	temp.LoadIdentity();

	float* m1 = m.GetData();
	float* m2 = temp.GetData();

	int i, j, k;
	float lu[20], *plu[4];
	
	// j行の要素の値の絶対値の最大値を plu[j][4] に求める
	for(j = 0; j < 4; ++j){
		float max = fabs(*(plu[j] = lu + 5 * j) = *(m1++));
		for(i = 0; ++i < 4;){
			float a = fabs(plu[j][i] = *(m1++));
			if(a > max){ max = a; }
		}
		if(max == 0.0f){ return temp; }
		plu[j][4] = 1.0f / max;
	}

	// ピボットを考慮した LU 分解
	float det = 1.0f;
	for(j = 0; j < 4; ++j){
		float max = fabs(plu[j][j] * plu[j][4]);
		i = j;
		for(k = j; ++k < 4;){
			float a = fabs(plu[k][j] * plu[k][4]);
			if(a > max){
				max = a;
				i = k;
			}
		}

		if(i > j){
			float* t = plu[j];
			plu[j] = plu[i];
			plu[i] = t;
			det = -det;
		}
		if(plu[j][j] == 0.0f){ return temp; }
		det *= plu[j][j];

		for(k = j; ++k < 4;){
			plu[k][j] /= plu[j][j];
			for(i = j; ++i < 4;){
				plu[k][i] -= plu[j][i] * plu[k][j];
			}
		}
	}

	// 逆行列を求める
	for(k = 0; k < 4; ++k){
		// m2に単位行列を設定
		for(i = 0; i < 4; ++i){
			m2[i * 4 + k] = (plu[i] == lu + k * 5) ? 1.0f : 0.0f;
		}

		// luから逆行列を求める
		for(i = 0; i < 4; ++i){
			for(j = i; ++j < 4;){
				m2[j * 4 + k] -= m2[i * 4 + k] * plu[j][i];
			}
		}
		for(i = 4; --i >= 0;){
			for(j = i; ++j < 4;){
				m2[i * 4 + k] -= plu[i][j] * m2[j * 4 + k];
			}
			m2[i * 4 + k] /= plu[i][i];
		}
	}

	return temp;
}

// 単位行列を設定
void Matrix::LoadIdentity()
{
	_11 = 1.0f; _12 = 0.0f; _13 = 0.0f; _14 = 0.0f;
	_21 = 0.0f; _22 = 1.0f; _23 = 0.0f; _24 = 0.0f;
	_31 = 0.0f; _32 = 0.0f; _33 = 1.0f; _34 = 0.0f;
	_41 = 0.0f; _42 = 0.0f; _43 = 0.0f; _44 = 1.0f;
}

} // namespace tkl