//******************************************************
// ファイル名：Quaternion(クォータニオンクラス)
// 作　成　日：2022/10/7
#include "Quaternion.h"

#include <cmath>
#include "Vector.h"

namespace tkl
{
//******************************************************
// クォータニオン同士の計算
Quaternion Quaternion::operator*(const Quaternion& q) const
{
	Quaternion temp;
	temp.mX = mW * q.mX + mX * q.mW + mZ * q.mY - mY * q.mZ;
	temp.mY = mW * q.mY + mY * q.mW + mX * q.mZ - mZ * q.mX;
	temp.mZ = mW * q.mZ + mZ * q.mW + mY * q.mX - mX * q.mY;
	temp.mW = mW * q.mW - mX * q.mX - mY * q.mY - mZ * q.mZ;
	return temp;
}

Quaternion& Quaternion::operator*=(const Quaternion& q)
{
	*this = *this * q;
	return *this;
}
//******************************************************

// 回転角と回転軸からクォータニオンを作成
Quaternion Quaternion::RotationAxis(const Vector3& axis, float rotate)
{
	Quaternion temp;
	float scalar = sinf(rotate / 2.0f);

	temp.mX = axis.mX * scalar;
	temp.mY = axis.mY * scalar;
	temp.mZ = axis.mZ * scalar;

	temp.mW = cosf(rotate / 2.0f);

	return temp; 
}

} // namespace tkl