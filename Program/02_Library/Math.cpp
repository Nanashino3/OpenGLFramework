#include "Math.h"

namespace tkl
{
int GetSidesPointAndPlane(const Vector3& v, const Vector3& pn, const Vector3& pv)
{
	Vector3 vec = v - pv;
	float a = Vector3::Dot(vec, pn);

	if(a > 0.0f){
		return 1;
	}else if(a < 0.0f){
		return -1;
	}
	return 0;
}

} // namespace tkl