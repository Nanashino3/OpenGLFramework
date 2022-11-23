#include <cmath>
#include "Intersect.h"
#include "../02_Library/Math.h"

namespace tkl
{
// “_‚Æ‹éŒ`‚ÌÕ“Ë”»’è
bool IsIntersectPointRect(float ph, float pv, float rh, float rv, int size)
{
	float left	 = rh - (size >> 1);
	float right	 = rh + (size >> 1);
	float top	 = rv + (size >> 1);
	float bottom = rv - (size >> 1);

	if(left > ph)	return false;
	if(right < ph)	return false;
	if(top < pv)	return false;
	if(bottom > pv)	return false;

	return true;
}

// ü•ª‚Æ•½–Ê‚ÌÕ“Ë”»’è
bool IsIntersectLinePlane(const Vector3& lineStart, const Vector3& lineEnd,
						  const Vector3& planePos, const Vector3& planeNormal,
						  Vector3* intersectPos)
{
	if(1 == GetSidesPointAndPlane(lineStart, planeNormal, planePos) && 1 == GetSidesPointAndPlane(lineEnd, planeNormal, planePos)) return false;
	if(-1 == GetSidesPointAndPlane(lineStart, planeNormal, planePos) && -1 == GetSidesPointAndPlane(lineEnd, planeNormal, planePos)) return false;

	Vector3 ln = lineEnd - lineStart;
	Vector3 pa = lineStart - planePos;
	Vector3 pb = lineEnd - planePos;

	float na = fabsf(Vector3::Dot(pa, planeNormal));
	float nb = fabsf(Vector3::Dot(pb, planeNormal));

	if(intersectPos) *intersectPos = lineStart + ln * (na / (na + nb));

	return true;
}

} // namespace tkl