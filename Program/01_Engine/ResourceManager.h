#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_
#include <memory>
#include <unordered_map>

namespace tkl
{
class Texture;
class SoundBuffer;
class ResourceManager
{
public:
	static ResourceManager* GetInstance();
	static void DestroyInstance();

	std::shared_ptr<Texture> CreateTextureFromFile(const char* fileName);
	std::shared_ptr<SoundBuffer> CreateSoundFromFile(const char* fileName);

private:
	ResourceManager();
	~ResourceManager();

	ResourceManager(const ResourceManager& other){}
	ResourceManager& operator=(const ResourceManager& other){}

private:
	static ResourceManager* sMyInstance;
	std::unordered_map<const char*, std::shared_ptr<Texture>> mCacheTextures;		// IDとテクスチャクラスを紐づける
};

} // namespace tkl

#endif