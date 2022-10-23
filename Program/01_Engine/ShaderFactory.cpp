#include "ShaderFactory.h"

#include "Shader.h"

// シングルトン
ShaderFactory* ShaderFactory::sInstance = nullptr;
ShaderFactory::ShaderFactory()
{}

ShaderFactory::~ShaderFactory()
{}

ShaderFactory* ShaderFactory::GetInstance()
{
	if(!sInstance){
		sInstance = new ShaderFactory;
	}
	return sInstance;
}
void ShaderFactory::DestroyInstance()
{
	delete sInstance;
}

// 組み立て
Shader* ShaderFactory::GetShader(std::string shaderName)
{
	// シェーダを生成済か
	auto iter = mCacheShaders.find(shaderName);
	if(iter != mCacheShaders.end()){ return iter->second; }

	// 新規シェーダを生成する
	std::string vertexFile = "Shader/" + shaderName + "Vert.glsl";
	std::string fragFile = "Shader/" + shaderName + "Frag.glsl";

	Shader* shader = new Shader();
	shader->LoadShader(vertexFile.c_str(), fragFile.c_str());
	mCacheShaders.emplace(shaderName, shader);

	return shader;
}