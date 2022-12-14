#include "ShaderFactory.h"
#include "Shader.h"

namespace tkl
{
ShaderFactory* ShaderFactory::sInstance = nullptr;
ShaderFactory::ShaderFactory()
{}

ShaderFactory::~ShaderFactory()
{}

ShaderFactory* ShaderFactory::GetInstance()
{
	if(!sInstance){ sInstance = new ShaderFactory; }
	return sInstance;
}
void ShaderFactory::DestroyInstance()
{
	delete sInstance;
}

// 組み立て
std::shared_ptr<Shader> ShaderFactory::GetShader(const std::string& shaderName)
{
	// シェーダを生成済か
	auto iter = mCacheShaders.find(shaderName);
	if(iter != mCacheShaders.end()){ return iter->second; }

	// 新規シェーダを生成する
	std::string vertexFile = "Shader/" + shaderName + "Vert.glsl";
	std::string fragFile = "Shader/" + shaderName + "Frag.glsl";

	std::shared_ptr<Shader> shader = std::make_shared<Shader>();
	shader->LoadShader(vertexFile.c_str(), fragFile.c_str());
	mCacheShaders.emplace(shaderName, shader);

	return shader;
}

} // namespace tkl