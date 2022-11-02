#pragma once

#include "../02_Library/Vector.h"
namespace tkl
{
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
}