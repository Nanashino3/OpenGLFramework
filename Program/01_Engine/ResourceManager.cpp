#include "ResourceManager.h"

#include <SOIL.h>
#include "Texture.h"

ResourceManager* ResourceManager::sMyInstance = nullptr;
ResourceManager::ResourceManager()
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

// ファイル名によるテクスチャ生成
std::shared_ptr<Texture> ResourceManager::CreateTextureFromFile(const char* fileName)
{
	auto iter = mCacheTextures.find(fileName);
	if(iter != mCacheTextures.end()){ return iter->second; }

	int channels = 0, textureW = 0, textureH = 0;
	unsigned char* image = SOIL_load_image(fileName, &textureW, &textureH, &channels, SOIL_LOAD_AUTO);
	if (image == nullptr) { return nullptr; }

	std::shared_ptr<Texture> newTexture = std::make_shared<Texture>(textureW, textureH, image, channels);
	mCacheTextures.emplace(fileName, newTexture);
	SOIL_free_image_data(image);
	return newTexture;
}