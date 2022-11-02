#pragma once

#include "../02_Library/Vector.h"
namespace tkl
{
bool IsIntersectLinePlane(const Vector3& lineStart, const Vector3& lineEnd,
						  const Vector3& planePos, const Vector3& planeNormal,
						  Vector3* intersectPos = nullptr);
}