#pragma once
#include <unordered_map>

class Shader;
class ShaderFactory
{
public:
	static ShaderFactory* GetInstance();
	static void DestroyInstance();

	Shader* GetShader(std::string shaderName);

private:
	ShaderFactory();
	~ShaderFactory();
	ShaderFactory(const ShaderFactory& other){}
	ShaderFactory& operator=(const ShaderFactory& other){}

private:
	static ShaderFactory* sInstance;

	std::unordered_map<std::string, Shader*> mCacheShaders;
};