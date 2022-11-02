#ifndef _MESHRENDERER_H_
#define _MESHRENDERER_H_

#include "Renderer.h"

namespace tkl
{
class MeshRenderer : public Renderer
{
public:
	MeshRenderer(const char* shaderName = "Lambert");
	virtual ~MeshRenderer();

private:
	virtual void ActualDraw(std::shared_ptr<tkl::Mesh> mesh) final;
	void SetLightUniforms();
};

} // namespace tkl

#endif