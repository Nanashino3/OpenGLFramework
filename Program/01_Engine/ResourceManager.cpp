#include "ResourceManager.h"

#include <iostream>
#include <SOIL.h>
#include "Texture.h"
#include "Sound/SoundParser.h"
#include "Sound/SoundBuffer.h"
#include "../02_Library/Utility.h"

namespace tkl
{
ResourceManager* ResourceManager::sMyInstance = nullptr;
ResourceManager::ResourceManager()
{}

ResourceManager::~ResourceManager()
{}

ResourceManager* ResourceManager::GetInstance()
{
	if(!sMyInstance) sMyInstance = new ResourceManager();
	return sMyInstance;
}

void ResourceManager::DestroyInstance()
{
	TKL_SAFE_DELETE(sMyInstance);
}

// テクスチャ生成(ファイル名)
std::shared_ptr<Texture> ResourceManager::CreateTextureFromFile(const char* fileName)
{
	auto iter = mCacheTextures.find(fileName);
	if(iter != mCacheTextures.end()){ return iter->second; }

	int channels = 0, textureW = 0, textureH = 0;
	unsigned char* image = SOIL_load_image(fileName, &textureW, &textureH, &channels, SOIL_LOAD_AUTO);
	if (image == nullptr) { std::cerr << "Failed to LoadImage." << std::endl; return nullptr; }

	std::shared_ptr<Texture> newTexture = std::make_shared<Texture>(textureW, textureH, image, channels);
	mCacheTextures.emplace(fileName, newTexture);
	SOIL_free_image_data(image);
	return newTexture;
}

// サウンド生成(ファイル名)
std::shared_ptr<SoundBuffer> ResourceManager::CreateSoundFromFile(const char* fileName)
{
//	auto iter = mCacheSounds.find(fileName);
//	if(iter != mCacheSounds.end()){ return iter->second; }

	// オーディオをロード
	tkl::SoundInfo sndInfo;
	if(!tkl::SoundParser::LoadAudio(fileName, sndInfo)){
		std::cerr << "Failed to LoadAudio." << std::endl;
		return nullptr;
	}
	
	std::shared_ptr<SoundBuffer> newBuffer = 
		std::make_shared<SoundBuffer>(sndInfo.format, &sndInfo.data[0], sndInfo.size, sndInfo.frequency);

//	mCacheSounds.emplace_back(buffer);
	return newBuffer;
}

} // namespace tkl