#include "ScreenCamera.h"

namespace tkl
{
ScreenCamera::ScreenCamera(int screenWidth, int screenHeight)
: Camera(screenWidth, screenHeight)
{}

ScreenCamera::~ScreenCamera()
{}

void ScreenCamera::Update()
{
	float w = static_cast<float>(mScreenWidth >> 1);
	float h = static_cast<float>(mScreenHeight >> 1);
	mView = tkl::Matrix::CreateIdentity();
	mProjection = tkl::Matrix::CreateOrthogonalProjection(-w, w, -h, h, 1.0f, -1.0f);
}

} // namespace tkl