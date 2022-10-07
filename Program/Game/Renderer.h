#pragma once
#include <memory>
#include <vector>
#include "../Library/Matrix.h"

class Shader;
class VertexArray;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Initialize();
	void Draw(VertexArray* vertexArray);

	void SetViewProjectionMatrix(const Matrix& m){ mViewProjection = m; }
	void SetWorldTransformMatrix(const Matrix& m){ mWorldTransform = m; }

private:
	void LoadShaders();
	void SetLightUniforms();

private:
	std::unique_ptr<Shader> mMeshShader;

	Matrix mViewProjection;
	Matrix mWorldTransform;
};