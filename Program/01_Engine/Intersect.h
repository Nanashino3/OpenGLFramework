#ifndef _INTERSECT_H_
#define _INTERSECT_H_

#include "../02_Library/Vector.h"
namespace tkl
{
	//*****************************************************************************
	// work... �_�Ƌ�`�̏Փˌ��m
	// arg1... �����������̓_
	// arg2... �c���������̓_
	// arg3... �����������̋�`���S
	// arg4... �c���������̋�`���S
	// arg5... ��`�̃T�C�Y
	// ret.... [�Փ˂��Ă��� : true]   [�Փ˂��Ă��Ȃ� : false]
	bool IsIntersectPointRect(float ph, float pv, float rh, float rv, int size);

	//*****************************************************************************
	// work... �����ƕ��ʂ̏Փ˔���
	// arg1... �����̎n�_
	// arg2... �����̏I�_
	// arg3... ���ʏ�̍��W ( 0, 0, 0 �ȊO )
	// arg4... ���ʂ̖@��
	// arg5... �Փ˓_�̎󂯎��p( �K�v�Ȃ���Ώȗ��� )
	// ret.... [�Փ˂��Ă��� : true] [�Փ˂��Ă��Ȃ� : false]
	// tips... �Փ˂��Ă��Ȃ��ꍇ arg5 �œn���������͕ω��Ȃ�
	bool IsIntersectLinePlane(const Vector3& lineStart, const Vector3& lineEnd,
							  const Vector3& planePos, const Vector3& planeNormal,
							  Vector3* intersectPos = nullptr);
} // namespace tkl

#endif