//******************************************************
// ファイル名：Quaternion(クォータニオンクラス)
// 作　成　日：2022/10/7
#ifndef _QUATERNION_H_
#define _QUATERNION_H_

namespace tkl
{
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

	//******************************************************
	// クォータニオン同士の計算
	Quaternion operator*(const Quaternion& q) const;
	Quaternion& operator*=(const Quaternion &q);
	//******************************************************

	// 回転角と回転軸からクォータニオンを作成
	static Quaternion RotationAxis(const Vector3& axis, float rotate);
};

} // namespace tkl

#endif