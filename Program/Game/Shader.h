#pragma once

class Shader
{
public:
	Shader();
	~Shader();

	void LoadShader();
	void SetMatrixUniform();

private:
	unsigned int mShaderProgram;
};