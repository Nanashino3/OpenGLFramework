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
	void SetView(const tkl::Matrix& view){ mView = view; }
	void SetProjection(const tkl::Matrix& projection){ mProjection = projection; }

protected:
	std::shared_ptr<Shader> mShader;
	tkl::Matrix mView;
	tkl::Matrix mProjection;
};

} // namespace tkl

#endif