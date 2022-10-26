#pragma once

#include <memory>
#include <unordered_map>

//class Mesh;
//class Renderer;
class Texture;
class ResourceManager
{
public:
	static ResourceManager* GetInstance();
	static void DestroyInstance();

//	void Initialize(int screenWidth, int screenHeight);
	int GetTextureHandle(const char* fileName);
	std::shared_ptr<Texture> CreateTextureFromFile(const char* fileName);
//	void DrawGraph(int posX, int posY, int textureID, int isTrans);

private:
	ResourceManager();
	~ResourceManager();

	ResourceManager(const ResourceManager& other){}
	ResourceManager& operator=(const ResourceManager& other){}

private:
	static ResourceManager* sMyInstance;

//	Mesh* mMesh;
//	Renderer* mRenderer;
	std::unordered_map<const char*, int> mCacheTextureID;					// ファイル名とIDを紐づける
	std::unordered_map<int, std::shared_ptr<Texture>> mCacheTextures;		// IDとテクスチャクラスを紐づける
};