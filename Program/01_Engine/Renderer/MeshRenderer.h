//****************************************************************************
// ファイル名：MeshRenderer(メッシュレンダラークラス)
// 作　成　日：2022/10/13
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

	virtual void Draw(std::shared_ptr<Mesh> mesh) final;

private:
	void SetLightUniforms(std::shared_ptr<Mesh> mesh);
};

} // namespace tkl

#endif