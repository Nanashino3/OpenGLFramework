//****************************************************************************
// �t�@�C�����FMatrix(�s��N���X)
// ��@���@���F2022/10/7
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
	// Matrix���m�̏�Z
	Matrix operator*(const Matrix& m) const;
	Matrix& operator*=(const Matrix& m);
	//***************************************************************************

	// �s��̔z���Ԃ�
	float* GetData() const { return (float*)&mMatrix[0]; }

	// �P�ʍs����쐬
	static Matrix CreateIdentity();
	// ���s�s����쐬
	static Matrix CreateTranslation(const Vector3& pos);
	// �g�k�s����쐬
	static Matrix CreateScale(const Vector3& scale);
	// �N�H�[�^�j�I������s����쐬
	static Matrix CreateRotationFromQuaternion(const Quaternion& q);
	// �����ˉe�s����쐬
	static Matrix CreatePerspectiveProjection(float angle, float aspect, float near, float far);
	// ���ˉe�s����쐬
	static Matrix CreateOrthogonalProjection(float left, float right, float bottom, float top, float near, float far);
	// �����s����쐬
	static Matrix CreateLookAt(const Vector3& camPos, const Vector3& targetPos, const Vector3& upVector);
	// �r���[�|�[�g�s����쐬
	static Matrix CreateViewport(int screenWidth, int screenHeight);
	// �t�s����쐬
	static Matrix CreateInverseMatrix(const Matrix& m);

private:
	// �P�ʍs���ݒ�
	void LoadIdentity();
};

} // namespace tkl

#endif