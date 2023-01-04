#include <cmath>
#include "Intersect.h"
#include "../02_Library/Math.h"

namespace tkl
{
//****************************************************************************
// �֐����FIsIntersectPointRect
// �T�@�v�F�Փˌ��m(�_�Ƌ�`)
// ���@���Farg1 �����������̓_
// �@�@�@�Farg2 �c���������̓_
// �@�@�@�Farg3 �����������̋�`���S
// �@�@�@�Farg4 �c���������̋�`���S
// �@�@�@�Farg5 ��`�̃T�C�Y
// �߂�l�F [�Փ˂��Ă��� : true]   [�Փ˂��Ă��Ȃ� : false]
// �ځ@�ׁF�_�Ƌ�`�̏Փˌ��m���s�����ʂ�Ԃ�
//****************************************************************************
bool IsIntersectPointRect(float ph, float pv, float rh, float rv, int size)
{
	return IsIntersectPointRect(ph, pv, rh, rv, size, size);
}

//****************************************************************************
// �֐����FIsIntersectPointRect
// �T�@�v�F�Փˌ��m(�_�Ƌ�`)
// ���@���Farg1 �����������̓_
// �@�@�@�Farg2 �c���������̓_
// �@�@�@�Farg3 �����������̋�`���S
// �@�@�@�Farg4 �c���������̋�`���S
// �@�@�@�Farg5 �������̋�`�T�C�Y
// �@�@�@�Farg6 �c�����̋�`�T�C�Y
// �߂�l�F [�Փ˂��Ă��� : true]   [�Փ˂��Ă��Ȃ� : false]
// �ځ@�ׁF�_�Ƌ�`�̏Փˌ��m���s�����ʂ�Ԃ�
//****************************************************************************
bool IsIntersectPointRect(float ph, float pv, float rh, float rv, int rhSize, int rvSize)
{
	float left	 = rh - (rhSize >> 1);
	float right	 = rh + (rhSize >> 1);
	float top	 = rv + (rvSize >> 1);
	float bottom = rv - (rvSize >> 1);

	if(left > ph)	{ return false; }
	if(right < ph)	{ return false; }
	if(top < pv)	{ return false; }
	if(bottom > pv)	{ return false; }

	return true;
}

//****************************************************************************
// �֐����FIsIntersectLinePlane
// �T�@�v�F�Փˌ��m(�����ƕ���)
// ���@���Farg1 �����̎n�_
// �@�@�@�Farg2 �����̏I�_
// �@�@�@�Farg3 ���ʏ�̍��W ( 0, 0, 0 �ȊO )
// �@�@�@�Farg4 ���ʂ̖@��
// �@�@�@�Farg4 �Փ˓_�̎󂯎��p( �K�v�Ȃ���Ώȗ��� )
// �߂�l�F [�Փ˂��Ă��� : true]   [�Փ˂��Ă��Ȃ� : false]
// �ځ@�ׁF�����Ƌ�`�̏Փˌ��m���s�����ʂ�Ԃ�
// �@�@�@�F�Փ˂��Ă��Ȃ��ꍇ arg5 �œn���������͕ω��Ȃ�
//****************************************************************************
bool IsIntersectLinePlane(const Vector3& lineStart, const Vector3& lineEnd,
						  const Vector3& planePos, const Vector3& planeNormal,
						  Vector3* intersectPos)
{
	if(1 == GetSidesPointAndPlane(lineStart, planeNormal, planePos) && 1 == GetSidesPointAndPlane(lineEnd, planeNormal, planePos)){ return false; }
	if(-1 == GetSidesPointAndPlane(lineStart, planeNormal, planePos) && -1 == GetSidesPointAndPlane(lineEnd, planeNormal, planePos)){ return false; }

	Vector3 ln = lineEnd - lineStart;
	Vector3 pa = lineStart - planePos;
	Vector3 pb = lineEnd - planePos;

	float na = fabsf(Vector3::Dot(pa, planeNormal));
	float nb = fabsf(Vector3::Dot(pb, planeNormal));

	if(intersectPos){ *intersectPos = lineStart + ln * (na / (na + nb)); }

	return true;
}

//****************************************************************************
// �֐����FIsIntersectAABB
// �T�@�v�F�Փˌ��m(AABB���m)
// ���@���Farg1 1�ڂ̑Ώۂ̈ʒu
// �@�@�@�Farg2 1�ڂ̑Ώۂ̃T�C�Y
// �@�@�@�Farg3 2�ڂ̑Ώۂ̈ʒu
// �@�@�@�Farg4 2�ڂ̑Ώۂ̃T�C�Y
// �߂�l�F [�Փ˂��Ă��� : true]   [�Փ˂��Ă��Ȃ� : false]
// �ځ@�ׁFAABB��AABB�̏Փˌ��m���s�����ʂ�Ԃ�
//****************************************************************************
bool IsIntersectAABB(const Vector3& v1, float v1Size, const Vector3& v2, float v2Size)
{
	tkl::Vector3 v1Min = tkl::Vector3(v1.mX - v1Size, v1.mY - v1Size, v1.mZ - v1Size);
	tkl::Vector3 v1Max = tkl::Vector3(v1.mX + v1Size, v1.mY + v1Size, v1.mZ + v1Size);
	tkl::Vector3 v2Min = tkl::Vector3(v2.mX - v2Size, v2.mY - v2Size, v2.mZ - v2Size);
	tkl::Vector3 v2Max = tkl::Vector3(v2.mX + v2Size, v2.mY + v2Size, v2.mZ + v2Size);

	return (v1Min.mX <= v2Max.mX && v1Max.mX >= v2Min.mX) && 
		   (v1Min.mY <= v2Max.mY && v1Max.mY >= v2Min.mY) && 
		   (v1Min.mZ <= v2Max.mZ && v1Max.mZ >= v2Min.mZ);
}

} // namespace tkl