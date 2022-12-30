//****************************************************************************
// ファイル名：ResourceManager(リソース管理者クラス)
// 作　成　日：2022/10/26
#include "ResourceManager.h"

#include <iostream>
#include <string>

#include <SOIL.h>
#include "Sound/SoundParser.h"
#include "Sound/SoundBuffer.h"
#include "Graphics/Geometry/Texture.h"
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
	if(!sMyInstance){ sMyInstance = new ResourceManager; }
	return sMyInstance;
}

void ResourceManager::DestroyInstance()
{
	TKL_SAFE_DELETE(sMyInstance);
}

//****************************************************************************
// 関数名：CreateTextureFromFile
// 概　要：テクスチャ生成(ファイル名)
// 引　数：arg1 ファイルパス
// 戻り値：Texture
// 詳　細：
//****************************************************************************
std::shared_ptr<Texture> ResourceManager::CreateTextureFromFile(const char* file)
{
	auto iter = mCacheTextures.find(file);
	if(iter != mCacheTextures.end()){ return iter->second; }

	int channels = 0, textureW = 0, textureH = 0;
	unsigned char* image = SOIL_load_image(file, &textureW, &textureH, &channels, SOIL_LOAD_AUTO);
	if (image == nullptr){ 
		std::cerr << "Failed to LoadImage : " << file << std::endl;
		return nullptr;
	}

	std::shared_ptr<Texture> newTexture = std::make_shared<Texture>();
	newTexture->CreateBuffer(textureW, textureH, image, channels);

	mCacheTextures.emplace(file, newTexture);
	SOIL_free_image_data(image);
	return newTexture;
}

//****************************************************************************
// 関数名：CreateSoundFromFile
// 概　要：サウンド生成(ファイル名)
// 引　数：arg1 ファイルパス
// 戻り値：SoundBuffer
// 詳　細：
//****************************************************************************
std::shared_ptr<SoundBuffer> ResourceManager::CreateSoundFromFile(const char* file)
{
	auto iter = mCacheSounds.find(file);
	if(iter != mCacheSounds.end()){ return iter->second; }

	// オーディオをロード
	tkl::SoundInfo sndInfo;
	if(!tkl::SoundParser::LoadAudio(file, sndInfo)){
		std::cerr << "Failed to LoadAudio : " << file << std::endl;
		return nullptr;
	}
	
	std::shared_ptr<SoundBuffer> newBuffer = 
		std::make_shared<SoundBuffer>(sndInfo.format, &sndInfo.data[0], sndInfo.size, sndInfo.frequency);
	mCacheSounds.emplace(file, newBuffer);
	return newBuffer;
}

//****************************************************************************
// 関数名：LoadFontFromTTF
// 概　要：フォントの読み込み(TTFファイル)
// 引　数：arg1 ファイルパス
// 戻り値：SoundBuffer
// 詳　細：
//****************************************************************************
bool ResourceManager::LoadFontFromTTF(const std::string& file)
{
	// ライブラリの初期化
	FT_Library ft;
	if(FT_Init_FreeType(&ft)){
		std::cerr << "Failed to Initialize FreeType." << std::endl;
		return false;
	}

	// フォントファイルの読み込み
	FT_Face face;
	if(FT_New_Face(ft, file.c_str(), 0, &face)){
		std::cerr << "Failed to load font." << std::endl;
		return false;
	}else{
		mNowFont = file;

		// ビットマップフォントのサイズを指定
		// TODO：32固定
		FT_Set_Pixel_Sizes(face, 0, 32);

		// TODO：ASCII文字(128文字分)対応
		// ひらがな・カタカナは未対応
		for(unsigned char c = 0; c < 128; ++c){
			if(FT_Load_Char(face, c, FT_LOAD_RENDER)){
				std::cerr << "Error : Failed to load Glyph." << std::endl;
				continue;
			}

			std::shared_ptr<Texture> newTexture = std::make_shared<Texture>();
			newTexture->CreateBufferFromTTF(face->glyph->bitmap);

			Vector3 bearing = Vector3(face->glyph->bitmap_left, face->glyph->bitmap_top, 0);
			Vector3 advance = Vector3(face->glyph->advance.x, face->glyph->advance.y, 0);
			mCacheFonts[file].emplace(c, std::make_tuple(newTexture, bearing, advance));
		}
	}

	// freetypeの開放
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	return true;
}

//****************************************************************************
// 関数名：GetFont
// 概　要：フォント取得
// 引　数：arg1 文字
// 戻り値：テクスチャ、offset、水平方向のオフセット
// 詳　細：
//****************************************************************************
std::tuple<std::shared_ptr<Texture>, Vector3, Vector3> ResourceManager::GetFont(char c)
{
	auto iter = mCacheFonts[mNowFont].find(c);
	if(iter != mCacheFonts[mNowFont].end()){ return iter->second; }

	return std::make_tuple(nullptr, Vector3(), Vector3());
}

} // namespace tkl