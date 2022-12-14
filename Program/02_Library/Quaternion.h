//******************************************************
// �t�@�C�����FQuaternion(�N�H�[�^�j�I���N���X)
// ��@���@���F2022/10/7
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
	// �N�H�[�^�j�I�����m�̌v�Z
	Quaternion operator*(const Quaternion& q) const;
	Quaternion& operator*=(const Quaternion &q);
	//******************************************************

	// ��]�p�Ɖ�]������N�H�[�^�j�I�����쐬
	static Quaternion RotationAxis(const Vector3& axis, float rotate);
};

} // namespace tkl

#endif