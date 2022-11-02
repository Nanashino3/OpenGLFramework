#ifndef _SHADER_H_
#define _SHADER_H_

namespace tkl
{
class Matrix;
class Vector3;
class Shader
{
public:
	Shader();
	~Shader();

	void LoadShader(const char* vertFileName, const char* fragFileName);
	void ActiveShader();
	
	void SetMatrixUniform(const char* name, const tkl::Matrix& matrix);
	void SetVectorUniform(const char* name, const tkl::Vector3& vector);
	void SetFloatUniform(const char* name, const float value);

private:
	unsigned int mShaderProgram;
};

} // namespace tkl

#endif