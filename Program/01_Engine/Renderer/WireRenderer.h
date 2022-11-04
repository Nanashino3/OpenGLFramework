#ifndef _WIRERENDERER_H_
#define _WIRERENDERER_H_

#include "Renderer.h"
namespace tkl
{
class WireRenderer : public Renderer
{
public:
	WireRenderer(const char* shaderName = "Basic");
	virtual ~WireRenderer();

	virtual void Draw(std::shared_ptr<Mesh> mesh) final;
//private:
//	virtual void ActualDraw(std::shared_ptr<Mesh> mesh) final;
};

} // namespace tkl

#endif