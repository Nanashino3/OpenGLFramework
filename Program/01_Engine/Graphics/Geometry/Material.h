#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "../../../02_Library/Vector.h"

namespace tkl
{
class Material
{
public:
	Material()
	: mAmbient(0.2f, 0.2f, 0.2f)
	, mDiffuse(1.0f, 1.0f, 1.0f)
	, mSpecular(0.25f, 0.25f, 0.25)
	{}
	~Material(){}

	void SetAmbient(const tkl::Vector3& ambient){ mAmbient = ambient; }
	const tkl::Vector3& GetAmbient() const { return mAmbient; }
	void SetDiffuse(const tkl::Vector3& diffuse){ mDiffuse = diffuse; }
	const tkl::Vector3& GetDiffuse() const { return mDiffuse; }
	void SetSpecular(const tkl::Vector3& specular){ mSpecular = specular; }
	const tkl::Vector3& GetSpecular() const { return mSpecular; }

private:
	Vector3 mAmbient;
	Vector3 mDiffuse;
	Vector3 mSpecular;
};

} // namespace tkl

#endif