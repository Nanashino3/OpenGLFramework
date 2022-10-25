#include "TextureManager.h"

#include "Texture.h"
#include "VertexArray.h"
#include "SpriteRenderer.h"
#include "../02_Library/Matrix.h"
#include "../02_Library/Utility.h"
#include "../02_Library/FontTexture.h"

TextureManager* TextureManager::sMyInstance = nullptr;
TextureManager::TextureManager()
: mRenderer(nullptr)
{
	mRenderer = new SpriteRenderer("Sprite");

	VertexArray::VERTEX vertices []= {
		{-0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f,  0.0f},
		{ 0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f,  0.0f},
		{ 0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f,  1.0f},
		{-0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f,  1.0f}
	};
	int indices[] = {
		0, 1, 2,
		0, 2, 3
	};
	int indicesNum = sizeof(indices) / sizeof(indices[0]);
	mSpriteVertex = new VertexArray(4, vertices, indicesNum, indices);
}

TextureManager::~TextureManager()
{}

TextureManager* TextureManager::GetInstance()
{
	if(!sMyInstance){
		sMyInstance = new TextureManager();
	}
	return sMyInstance;
}

void TextureManager::DestroyInstance()
{
	delete sMyInstance;
}

void TextureManager::Initialize(int screenWidth, int screenHeight)
{
	int width = screenWidth >> 1;
	int height = screenHeight >> 1;
	tkl::Matrix vpm = tkl::Matrix::CreateOrthogonalProjection(-width, width, -height, height, 1.0f, -1.0f);
	mRenderer->SetViewProjection(vpm);
}

// 既にフォント作成すみか
bool TextureManager::IsCreateFont(wchar_t once)
{
	auto iter = mCacheFonts.find(once);
	return iter != mCacheFonts.end();
}

// フォントテクスチャを作成
void TextureManager::CreateFontTexture(float posX, float posY, wchar_t once)
{
	auto texture = tnl::CreateFontTexture(32, once);
	
	char* colorArray  = std::get<0>(texture).get();
	int textureWidth  = std::get<1>(texture);
	int textureHeight = std::get<2>(texture);

	Texture* newTexture = new Texture(textureWidth, textureHeight, colorArray);
	newTexture->mPosition = tkl::Vector3(posX, posY, 1.0f);
	mCacheFonts.emplace(once, newTexture);
}

// 描画
void TextureManager::Draw(wchar_t once)
{
	auto iter = mCacheFonts.find(once);
	if(iter != mCacheFonts.end()){ mRenderer->Draw(iter->second); }
}