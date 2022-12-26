//****************************************************************************
// �t�@�C�����FMeshRenderer(���b�V�������_���[�N���X)
// ��@���@���F2022/10/13
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