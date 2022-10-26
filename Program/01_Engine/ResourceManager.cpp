#include "ResourceManager.h"

#include <SOIL.h>
//#include "Mesh.h"
#include "Texture.h"
#include "VertexArray.h"
//#include "Renderer/SpriteRenderer.h"

ResourceManager* ResourceManager::sMyInstance = nullptr;
ResourceManager::ResourceManager()
//: mMesh(new Mesh)
//, mRenderer(new SpriteRenderer())
{}

ResourceManager::~ResourceManager()
{}

ResourceManager* ResourceManager::GetInstance()
{
	if(!sMyInstance){
		sMyInstance = new ResourceManager();
	}
	return sMyInstance;
}

void ResourceManager::DestroyInstance()
{
	delete sMyInstance;
}

//void ResourceManager::Initialize(int screenWidth, int screenHeight)
//{
//	float w = static_cast<float>(screenWidth >> 1);
//	float h = static_cast<float>(screenHeight >> 1);
//
//	tkl::Matrix vpm = tkl::Matrix::CreateOrthogonalProjection(-w, w, -h, h, 1.0f, -1.0f);
//	mRenderer->SetViewProjection(vpm);
//
//	VertexArray::VERTEX vertices[] = {
//		{-0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f,  0.0f},
//		{ 0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f,  0.0f},
//		{ 0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f,  1.0f},
//		{-0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f,  1.0f}
//	};
//
//	int indices[] = {
//		0, 1, 2,
//		2, 3, 0
//	};
//
//	int indicesNum = sizeof(indices) / sizeof(indices[0]);
//	mMesh->SetVertex(std::make_shared<VertexArray>(4, vertices, indicesNum, indices));
//}

// テクスチャハンドルの取得
int ResourceManager::GetTextureHandle(const char* fileName)
{
	auto iter = mCacheTextureID.find(fileName);
	if(iter != mCacheTextureID.end()){ return iter->second; }

	// 新しくテクスチャを生成
	std::shared_ptr<Texture> newTexture = CreateTextureFromFile(fileName);
	mCacheTextureID.emplace(fileName, newTexture->GetTextureID());
	mCacheTextures.emplace(newTexture->GetTextureID(), newTexture);

	return newTexture->GetTextureID();
}

// ファイル名によるテクスチャ生成
std::shared_ptr<Texture> ResourceManager::CreateTextureFromFile(const char* fileName)
{
	int channels = 0, textureW = 0, textureH = 0;
	unsigned char* image = SOIL_load_image(fileName, &textureW, &textureH, &channels, SOIL_LOAD_AUTO);
	if (image == nullptr) { return nullptr; }

	std::shared_ptr<Texture> newTexture = std::make_shared<Texture>(textureW, textureH, image, channels);
	SOIL_free_image_data(image);
	return newTexture;
}

//void ResourceManager::DrawGraph(int posX, int posY, int textureID, int isTrans)
//{
//	// IDからテクスチャを取得する
//	auto iter = mCacheTextures.find(textureID);
//	if(iter == mCacheTextures.end()){ return; }
//
//	std::shared_ptr<Texture> texture = iter->second;
//	mMesh->SetPosition(tkl::Vector3(posX, posY, 1.0f));
//	mMesh->SetScale(tkl::Vector3(texture->GetTextureWidth(), texture->GetTextureHeight(), 1.0f));
//	mMesh->SetTexture(texture);
//	mRenderer->Draw(mMesh);
//}