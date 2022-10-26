#pragma once
#include <memory>
#include <unordered_map>

class Texture;
class ResourceManager
{
public:
	static ResourceManager* GetInstance();
	static void DestroyInstance();

	std::shared_ptr<Texture> CreateTextureFromFont(wchar_t once);
	std::shared_ptr<Texture> CreateTextureFromFile(const char* fileName);

private:
	ResourceManager();
	~ResourceManager();

	ResourceManager(const ResourceManager& other){}
	ResourceManager& operator=(const ResourceManager& other){}

private:
	static ResourceManager* sMyInstance;
	std::unordered_map<const char*, std::shared_ptr<Texture>> mCacheTextures;		// IDとテクスチャクラスを紐づける
};