//****************************************************************************
// �t�@�C�����FVector(�x�N�g���N���X)
// ��@���@���F2022/10/6
#ifndef _VECTOR_H_
#define _VECTOR_H_

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

	Vector3() : mX(0.0f), mY(0.0f), mZ(0.0f){}
	Vector3(float x, float y, float z) : mX(x), mY(y), mZ(z){}

	//******************************************************
	// �P�����Z�q
	Vector3 operator-() const;
	//******************************************************

	//******************************************************
	// �x�N�g�����m�̌v�Z
	Vector3 operator+(const Vector3& a) const;
	Vector3& operator+=(const Vector3& a);
	Vector3 operator-(const Vector3& a) const;
	Vector3& operator-=(const Vector3& a);
	bool operator==(const Vector3& a);
	//******************************************************

	//******************************************************
	// �x�N�g���ƃX�J���[�̌v�Z
	Vector3 operator+(float s) const;
	Vector3& operator+=(float s);
	Vector3 operator-(float s) const;
	Vector3& operator-=(float s);
	Vector3 operator*(float s) const;
	Vector3& operator*=(float s);
	//******************************************************

	// �x�N�g���̔z���Ԃ�
	float* GetData() const { return (float*)(&mVec[0]); }

	// �x�N�g���̐��K��
	static Vector3 Normalize(const Vector3& v);
	// �x�N�g���̊O��
	static Vector3 Cross(const Vector3& v1, const Vector3& v2);
	// �x�N�g���̓���
	static float Dot(const Vector3& v1, const Vector3& v2);
	// 2�_�Ԃ̋��������߂�
	static float Distance(const Vector3& v1, const Vector3& v2);
	// ���������߂�
	static float Magnitude(const Vector3& v1);

	// �x�N�g�����N�H�[�^�j�I���Ɏˉe����
	static Vector3 TransformCoord(const Vector3& v, const Quaternion& q);
	// �x�N�g�����}�g���b�N�X�Ɏˉe����
	static Vector3 TransformCoord(const Vector3& v, const Matrix& m);
	// �X�N���[����Ƀ��C���쐬
	static Vector3 CreateScreenRay(const Vector3& screenPos, int screenW, int screenH, const tkl::Matrix& view, const tkl::Matrix& projection);

	static Vector3 ConvertWorldPosToScreenPos(int screenW, int screenH, const tkl::Vector3& worldPos, const tkl::Matrix& view, const tkl::Matrix& projection);

	static const Vector3 ZERO;
	static const Vector3 UNITX;
	static const Vector3 UNITY;
	static const Vector3 UNITZ;
	static const Vector3 NEG_UNITX;
	static const Vector3 NEG_UNITY;
	static const Vector3 NEG_UNITZ;
};

} // namespace tkl

#endif