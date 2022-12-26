//****************************************************************************
// �t�@�C�����FWireRenderer(���C���[�����_���[�N���X)
// ��@���@���F2022/10/13
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
};

} // namespace tkl

#endif