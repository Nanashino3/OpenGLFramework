#pragma once

class Shader;
class Camera;
class Mesh;

class Renderer
{
public:
	Renderer(Mesh* mesh, const char* shaderName);
	~Renderer();

	virtual void Draw(Mesh* mesh, Camera* camera);

private:
	virtual void ActualDraw(Mesh* mesh) = 0;

protected:
	Shader* mShader;
};