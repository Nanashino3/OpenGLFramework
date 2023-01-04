#ifndef _SHADERFACTORY_H_
#define _SHADERFACTORY_H_
#include <memory>
#include <string>
#include <unordered_map>

namespace tkl
{
class Shader;
class ShaderFactory
{
public:
	static ShaderFactory* GetInstance();
	static void DestroyInstance();

	std::shared_ptr<Shader> GetShader(const std::string& shaderName);

private:
	ShaderFactory();
	~ShaderFactory();
	ShaderFactory(const ShaderFactory& other){}
	ShaderFactory& operator=(const ShaderFactory& other){}

private:
	static ShaderFactory* sInstance;
	std::unordered_map<std::string, std::shared_ptr<Shader>> mCacheShaders;
};

} // namespace tkl

#endif