#include "Vector.h"

#include <math.h>
#include "Quaternion.h"

const Vector3 Vector3::ZERO(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNITX(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNITY(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UNITZ(0.0f, 0.0f, 1.0f);

// �x�N�g���̐��K��
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

// �x�N�g�����N�H�[�^�j�I���ŉ�]������
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