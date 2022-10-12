#pragma once

class Shader;
class Camera;
class Mesh;

class Renderer
{
public:
	Renderer(Mesh* mesh);
	~Renderer();

	void LoadShader(const char* vertexFile, const char* fragFile);
	virtual void Draw(Camera* camera);
protected:
	Shader* mShader;
	Mesh* mMesh;
};