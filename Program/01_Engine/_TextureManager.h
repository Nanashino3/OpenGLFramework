#pragma once
#include <unordered_map>

class VertexArray;
class Texture;
class SpriteRenderer;
class TextureManager
{
public:
	static TextureManager* GetInstance();
	static void DestroyInstance();

	void Initialize(int screenWidth, int screenHeight);
	bool IsCreateFont(wchar_t once);
	void CreateFontTexture(float posX, float posY, wchar_t once);
	void Draw(wchar_t once);

private:
	TextureManager();
	~TextureManager();

	TextureManager(const TextureManager& other) {}
	TextureManager& operator=(const TextureManager& other) {}

private:
	static TextureManager* sMyInstance;

	SpriteRenderer* mRenderer;
	VertexArray* mSpriteVertex;

	std::unordered_map<wchar_t, Texture*> mCacheFonts;
};