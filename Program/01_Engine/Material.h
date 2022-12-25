#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "../02_Library/Vector.h"

namespace tkl
{
class Material
{
public:
	Material()
	: mAmbient(1.0f, 1.0f, 1.0f)
	, mDiffuse(1.0f, 1.0f, 1.0f)
	{}
	~Material(){}

	void SetAmbient(const tkl::Vector3& ambient){ mAmbient = ambient; }
	const tkl::Vector3& GetAmbient() const { return mAmbient; }
	void SetDiffuse(const tkl::Vector3& diffuse){ mDiffuse = diffuse; }
	const tkl::Vector3& GetDiffuse() const { return mDiffuse; }

private:
	Vector3 mAmbient;
	Vector3 mDiffuse;
	Vector3 mSpecular;
};

} // namespace tkl

#endif