#include "RendererFactory.h"

#include <iostream>
#include "MeshRenderer.h"
#include "WireRenderer.h"

RendererFactory::RendererFactory(Mesh* mesh)
: mMesh(mesh)
{}

RendererFactory::~RendererFactory()
{}

std::unique_ptr<Renderer> RendererFactory::Build(BUILD_TYPE type)
{
	std::unique_ptr<Renderer> renderer = nullptr;
	switch (type)
	{
	case BUILD_MESH:
		renderer = std::make_unique<MeshRenderer>(mMesh);
		renderer->LoadShader("Shader/LambertVert.glsl", "Shader/LambertFrag.glsl");
		break;
	case BUILD_WIRE:
		renderer = std::make_unique<WireRenderer>(mMesh);
		renderer->LoadShader("Shader/PointVert.glsl", "Shader/PointFrag.glsl");
		break;
	default:
		std::cout << "Error : Can't Renderer Build. Build type : " << type << std::endl;
		break;
	}
	return renderer;
}