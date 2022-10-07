#include "Vector.h"

#include <math.h>

const Vector3 Vector3::ZERO(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNITX(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNITY(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UNITZ(0.0f, 0.0f, 1.0f);

// ƒxƒNƒgƒ‹‚Ì³‹K‰»
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