#pragma once

class Matrix;
class Vector3;
class Shader
{
public:
	Shader();
	~Shader();

	void LoadShader(const char* vertFileName, const char* fragFileName);
	void ActiveShader();
	
	void SetMatrixUniform(const char* name, const Matrix& matrix);
	void SetVectorUniform(const char* name, const Vector3& vector);
	void SetFloatUniform(const char* name, const float value);

private:
	unsigned int mShaderProgram;
};