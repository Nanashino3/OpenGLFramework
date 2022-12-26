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

// �g�ݗ���
std::shared_ptr<Shader> ShaderFactory::GetShader(std::string shaderName)
{
	// �V�F�[�_�𐶐��ς�
	auto iter = mCacheShaders.find(shaderName);
	if(iter != mCacheShaders.end()){ return iter->second; }

	// �V�K�V�F�[�_�𐶐�����
	std::string vertexFile = "Shader/" + shaderName + "Vert.glsl";
	std::string fragFile = "Shader/" + shaderName + "Frag.glsl";

	std::shared_ptr<Shader> shader = std::make_shared<Shader>();
	shader->LoadShader(vertexFile.c_str(), fragFile.c_str());
	mCacheShaders.emplace(shaderName, shader);

	return shader;
}

} // namespace tkl