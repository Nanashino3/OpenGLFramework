#ifndef _INTERSECT_H_
#define _INTERSECT_H_

#include "../02_Library/Vector.h"
namespace tkl
{
	bool IsIntersectPointRect(float ph, float pv, float rh, float rv, int size);
	bool IsIntersectLinePlane(const Vector3& lineStart, const Vector3& lineEnd,
							  const Vector3& planePos, const Vector3& planeNormal,
							  Vector3* intersectPos = nullptr);
	bool IsIntersectAABB(const Vector3& v1, float v1Size, const Vector3& v2, float v2Size);
} // namespace tkl

#endif