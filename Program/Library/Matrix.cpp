#include "Matrix.h"
#include "Vector.h"
#include "Quaternion.h"

// 平行行列を作成
Matrix Matrix::CreateTranslation(const Vector3& pos)
{
	Matrix temp;
	temp.LoadIdentity();
	temp[12] = pos.mX;
	temp[13] = pos.mY;
	temp[14] = pos.mZ;
	return temp;
}

// 拡縮行列を作成
Matrix Matrix::CreateScale(const Vector3& scale)
{
	Matrix temp;
	temp.LoadIdentity();
	temp[0]  = scale.mX;
	temp[5]  = scale.mY;
	temp[10] = scale.mZ;
	return temp;
}

// クォータニオンから行列を作成
Matrix Matrix::CreateRotationFromQuaternion(const Quaternion& q)
{
	Matrix temp;
	temp.LoadIdentity();

	temp[0]  = 1.0f - 2.0f * q.mY * q.mY - 2.0f * q.mZ * q.mZ;
	temp[1]  = 2.0f * q.mX * q.mY + 2.0f * q.mW * q.mZ;
	temp[2]  = 2.0f * q.mX * q.mZ - 2.0f * q.mW * q.mY;

	temp[4]  = 2.0f * q.mX * q.mY - 2.0f * q.mW * q.mZ;
	temp[5]  = 1.0f - 2.0f * q.mX * q.mX - 2.0f * q.mZ * q.mZ;
	temp[6]  = 2.0f * q.mY * q.mZ + 2.0f * q.mW * q.mX;

	temp[8]  = 2.0f * q.mX * q.mZ + 2.0f * q.mW * q.mY;
	temp[9]  = 2.0f * q.mY * q.mZ - 2.0f * q.mW * q.mX;
	temp[10] = 1.0f - 2.0f * q.mX * q.mX - 2.0f * q.mY * q.mY;

	return temp;
}