#include "Quaternion.h"

#include <math.h>
#include "Vector.h"

Quaternion Quaternion::RotationAxis(const Vector3& axis, float rotate)
{
	Quaternion temp;
	float scalar = sinf(rotate / 2.0f);

	temp.mX = axis.mX * scalar;
	temp.mY = axis.mY * scalar;
	temp.mZ = axis.mZ * scalar;

	return temp; 
}