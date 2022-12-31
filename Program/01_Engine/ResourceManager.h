//****************************************************************************
// ファイル名：ResourceManager(リソース管理者クラス)
// 作　成　日：2022/10/26
#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include <memory>
#include <unordered_map>
#include <string>
#include "../02_Library/Vector.h"

namespace tkl
{
class Texture;
class SoundBuffer;
class ResourceManager
{
public:
	static ResourceManager* GetInstance();
	static void DestroyInstance();

	bool LoadFontFromTTF(const std::string& file);
	std::tuple<std::shared_ptr<Texture>, Vector3, Vector3> GetFont(char c, int fontSize);

	std::shared_ptr<Texture> CreateTextureFromFile(const char* file);
	std::shared_ptr<SoundBuffer> CreateSoundFromFile(const char* file);
private:
	ResourceManager();
	~ResourceManager();

	ResourceManager(const ResourceManager& other){}
	ResourceManager& operator=(const ResourceManager& other){}

private:
	static ResourceManager* sMyInstance;
	std::unordered_map<const char*, std::shared_ptr<Texture>> mCacheTextures;
	std::unordered_map<const char*, std::shared_ptr<SoundBuffer>> mCacheSounds;
	std::unordered_map<int, std::unordered_map<unsigned char, std::tuple<std::shared_ptr<Texture>, Vector3, Vector3>>> mCacheFonts;
};

} // namespace tkl

#endif