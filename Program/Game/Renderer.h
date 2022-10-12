#pragma once
#include <memory>
#include <vector>
#include "../Library/Matrix.h"

class Camera;
class Shader;
class MeshComponent;
class WireComponent;
class Renderer
{
public:
	Renderer();
	~Renderer();

	void Initialize();
	void Draw(Camera* camera);

	void SetViewProjectionMatrix(const Matrix& m){ mViewProjection = m; }
	void AddMeshComponent(MeshComponent* comp){ mMeshComponents.emplace_back(comp); }
	void AddWireComponent(WireComponent* comp){ mWireComponents.emplace_back(comp); }
private:
	void LoadShaders();
	void SetLightUniforms(Shader* shader);

private:
	std::unique_ptr<Shader> mMeshShader;
	std::unique_ptr<Shader> mWireframeShader;

	Matrix mViewProjection;

	std::vector<MeshComponent*> mMeshComponents;
	std::vector<WireComponent*> mWireComponents;
};