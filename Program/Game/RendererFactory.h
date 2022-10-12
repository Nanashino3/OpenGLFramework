#pragma once
#include <memory>

class Mesh;
class Renderer;
class RendererFactory
{
public:
	enum BUILD_TYPE
	{
		BUILD_MESH,
		BUILD_WIRE,

		MAX_BUILD_TYPE
	};
	RendererFactory(Mesh* mesh);
	~RendererFactory();

	std::unique_ptr<Renderer> Build(BUILD_TYPE type);

private:
	Mesh* mMesh;
};