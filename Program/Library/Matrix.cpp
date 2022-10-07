#include "Matrix.h"

#include <math.h>
#include "Vector.h"
#include "Quaternion.h"
#include "Math.h"

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

// 透視射影行列の作成
Matrix Matrix::CreatePerspectiveProjection(float angle, float aspect, float near, float far)
{
	Matrix temp;
	temp.LoadIdentity();
	float fovy = tkl::ToRadian(angle);

	float fsn = far - near;
	if(fsn != 0.0f){
		temp[5] = 1.0f / tanf(fovy * 0.5f);
		temp[0] = temp[5] / aspect;
		temp[10] = -(far + near) / fsn;
		temp[11] = -1.0f;
		temp[14] = -2.0f * far * near / fsn;
		temp[15] = 0.0f;
	}

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
	temp[0]  = xAxis.mX; temp[1] = yAxis.mX; temp[2] = zAxis.mX;
	temp[4]  = xAxis.mY; temp[5] = yAxis.mY; temp[6] = zAxis.mY;
	temp[8]  = xAxis.mZ; temp[9] = yAxis.mZ; temp[10] = zAxis.mZ;
	temp[12] = trans.mX; temp[13] = trans.mY; temp[14] = trans.mZ;
	return temp;
}