#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <memory>
#include "../../02_Library/Matrix.h"

namespace tkl
{
class Mesh;
class Shader;
class Renderer
{
public:
	Renderer(const char* shaderName);
	~Renderer();

	virtual void Draw(std::shared_ptr<Mesh> mesh);
	void SetViewProjection(const tkl::Matrix& vp){ mViewProjection = vp; }

//private:
//	virtual void ActualDraw(std::shared_ptr<Mesh> mesh) = 0;

protected:
	std::shared_ptr<Shader> mShader;
	tkl::Matrix mViewProjection;
};

} // namespace tkl

#endif