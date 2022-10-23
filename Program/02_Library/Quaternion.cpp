#include "Quaternion.h"

#include <cmath>
#include "Vector.h"

namespace tkl
{
Quaternion Quaternion::RotationAxis(const Vector3& axis, float rotate)
{
	Quaternion temp;
	float scalar = sinf(rotate / 2.0f);

	temp.mX = axis.mX * scalar;
	temp.mY = axis.mY * scalar;
	temp.mZ = axis.mZ * scalar;

	temp.mW = cosf(rotate / 2.0f);

	return temp; 
}

} // namespace tkl