#pragma once

class Shader;
class Camera;
class Mesh;

class Renderer
{
public:
	Renderer(Mesh* mesh, const char* shaderName);
	~Renderer();

	virtual void Draw(Camera* camera);
protected:
	Shader* mShader;
	Mesh* mMesh;
};