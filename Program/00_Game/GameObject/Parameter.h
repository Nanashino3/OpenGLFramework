#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#include <memory>

namespace tkl { class Camera; }

class Parameter
{
public:
	Parameter()
	: mDeltaTime(0.0f)
	, mCamera(nullptr)
	{}
	virtual ~Parameter(){}

	void SetDeltaTime(float value) { mDeltaTime = value; }
	float GetDeltaTime() const { return mDeltaTime; }
	void SetCamera(std::shared_ptr<tkl::Camera> camera) { mCamera = camera; }
	std::shared_ptr<tkl::Camera> GetCamera() { return mCamera; }

private:
	float mDeltaTime;
	std::shared_ptr<tkl::Camera> mCamera;
};

#endif