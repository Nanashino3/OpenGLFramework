#pragma once
#include "../02_Library/Matrix.h"

class Shader;
class Renderer
{
public:
	Renderer(const char* shaderName);
	~Renderer();

	void Draw(void* drawObject);
	void SetViewProjection(const tkl::Matrix& vp){ mViewProjection = vp; }

private:
	virtual void ActualDraw(void* drawObject) = 0;

protected:
	Shader* mShader;

private:
	tkl::Matrix mViewProjection;
};