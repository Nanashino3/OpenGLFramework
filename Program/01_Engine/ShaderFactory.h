#pragma once
#include <memory>
#include <unordered_map>

class Shader;
class ShaderFactory
{
public:
	static ShaderFactory* GetInstance();
	static void DestroyInstance();

	std::shared_ptr<Shader> GetShader(std::string shaderName);

private:
	ShaderFactory();
	~ShaderFactory();
	ShaderFactory(const ShaderFactory& other){}
	ShaderFactory& operator=(const ShaderFactory& other){}

private:
	static ShaderFactory* sInstance;
	std::unordered_map<std::string, std::shared_ptr<Shader>> mCacheShaders;
};