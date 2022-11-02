#include "FixedCamera.h"

namespace tkl
{
FixedCamera::FixedCamera(int screenWidth, int screenHeight)
: Camera(screenWidth, screenHeight)
{}

FixedCamera::~FixedCamera()
{}

void FixedCamera::Update()
{
	float w = static_cast<float>(mScreenWidth >> 1);
	float h = static_cast<float>(mScreenHeight >> 1);
	mViewProjection = tkl::Matrix::CreateOrthogonalProjection(-w, w, -h, h, 1.0f, -1.0f);
}

} // namespace tkl