#include "Vector.h"

#include <cmath>
#include "Matrix.h"
#include "Quaternion.h"

namespace tkl
{
const Vector3 Vector3::ZERO(0, 0, 0);
const Vector3 Vector3::UNITX(1, 0, 0);
const Vector3 Vector3::UNITY(0, 1, 0);
const Vector3 Vector3::UNITZ(0, 0, 1);
const Vector3 Vector3::NEG_UNITX(-1,  0,  0);
const Vector3 Vector3::NEG_UNITY( 0, -1,  0);
const Vector3 Vector3::NEG_UNITZ( 0,  0, -1);

//******************************************************
// ベクトル同士
Vector3 Vector3::operator+(const Vector3& a) const
{
	return Vector3(mX + a.mX, mY + a.mY, mZ + a.mZ);
}
Vector3& Vector3::operator+=(const Vector3& a)
{
	*this = *this + a;
	return *this;
}
Vector3 Vector3::operator-(const Vector3& a) const
{
	return Vector3(mX - a.mX, mY - a.mY, mZ - a.mZ);
}
Vector3& Vector3::operator-=(const Vector3& a)
{
	*this = *this - a;
	return *this;
}
//******************************************************

//******************************************************
// ベクトルと定数計算
Vector3 Vector3::operator+(float s) const
{
	return Vector3(mX + s, mY + s, mZ + s);
}
Vector3& Vector3::operator+=(float s)
{
	*this = *this + s;
	return *this;
}
Vector3 Vector3::operator-(float s) const
{
	return Vector3(mX - s, mY - s, mZ - s);
}
Vector3& Vector3::operator-=(float s)
{
	*this = *this - s;
	return *this;
}
Vector3 Vector3::operator*(float s) const
{
	return Vector3(mX * s, mY * s, mZ * s);
}
Vector3& Vector3::operator*=(float s)
{
	*this = *this * s;
	return *this;
}
//******************************************************

// ベクトルの正規化
Vector3 Vector3::Normalize(const Vector3& v)
{
	Vector3 temp;
	float length = sqrtf(v.mX * v.mX + v.mY * v.mY + v.mZ * v.mZ);
	length = (length > 0.0f) ? 1.0 / length : length;

	temp.mX = v.mX * length;
	temp.mY = v.mY * length;
	temp.mZ = v.mZ * length;

	return temp;
}

// ベクトルの外積
Vector3 Vector3::Cross(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp;
	temp.mX = v1.mY * v2.mZ - v1.mZ * v2.mY;
	temp.mY = v1.mZ * v2.mX - v1.mX * v2.mZ;
	temp.mZ = v1.mX * v2.mY - v1.mY * v2.mX;
	return temp;
}

// ベクトルの内積
float Vector3::Dot(const Vector3& v1, const Vector3& v2)
{
	return v1.mX * v2.mX + v1.mY * v2.mY + v1.mZ * v2.mZ;
}

// ベクトルをクォータニオンに射影する
Vector3 Vector3::TransformCoord(const Vector3& v, const Quaternion& q)
{
	float w = -q.mX * v.mX - q.mY * v.mY - q.mZ * v.mZ;
	float x =  q.mY * v.mZ - q.mZ * v.mY + q.mW * v.mX;
	float y =  q.mZ * v.mX - q.mX * v.mZ + q.mW * v.mY;
	float z =  q.mX * v.mY - q.mY * v.mX + q.mW * v.mZ;

	float vx = y * -q.mZ + z * q.mY - w * q.mX + x * q.mW;
	float vy = z * -q.mX + x * q.mZ - w * q.mY + y * q.mW;
	float vz = x * -q.mY + y * q.mX - w * q.mZ + z * q.mW;

	return Vector3(vx, vy, vz);
}

// ベクトルをマトリックスに射影する
Vector3 Vector3::TransformCoord(const Vector3& v, const Matrix& m)
{
	tkl::Matrix tm = tkl::Matrix::CreateTranslation(v) ;
	tkl::Matrix wm = m * tm;

	return Vector3(wm._14, wm._24, wm._34);
}

// スクリーン上にレイを作成
Vector3 Vector3::CreateScreenRay(int screenX, int screenY, int screenW, int screenH, const tkl::Matrix& view, const tkl::Matrix& projection)
{
	// ビューポート行列を作成
	Matrix viewport = tkl::Matrix::CreateViewport(screenW, screenH);

	// スクリーン座標からワールド座標を計算
	Matrix tempView = view;
	tempView[12] = 0.0f;
	tempView[13] = 0.0f;
	tempView[14] = 0.0f;
	
	Matrix invViewport = tkl::Matrix::CreateInverseMatrix(viewport);
	Matrix invProjection = tkl::Matrix::CreateInverseMatrix(projection);
	Matrix invView = tkl::Matrix::CreateInverseMatrix(tempView);
	Matrix tempMatrix = invView * invProjection * invViewport;

	Vector3 tempVector = tkl::Vector3(static_cast<float>(screenX),
									  static_cast<float>(screenY),
									  0.0f);

	return tkl::Vector3::TransformCoord(tempVector, tempMatrix);
}

} // namespace tkl