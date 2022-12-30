//****************************************************************************
// �t�@�C�����FResourceManager(���\�[�X�Ǘ��҃N���X)
// ��@���@���F2022/10/26
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
// �֐����FCreateTextureFromFile
// �T�@�v�F�e�N�X�`������(�t�@�C����)
// ���@���Farg1 �t�@�C���p�X
// �߂�l�FTexture
// �ځ@�ׁF
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
// �֐����FCreateSoundFromFile
// �T�@�v�F�T�E���h����(�t�@�C����)
// ���@���Farg1 �t�@�C���p�X
// �߂�l�FSoundBuffer
// �ځ@�ׁF
//****************************************************************************
std::shared_ptr<SoundBuffer> ResourceManager::CreateSoundFromFile(const char* file)
{
	auto iter = mCacheSounds.find(file);
	if(iter != mCacheSounds.end()){ return iter->second; }

	// �I�[�f�B�I�����[�h
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
// �֐����FLoadFontFromTTF
// �T�@�v�F�t�H���g�̓ǂݍ���(TTF�t�@�C��)
// ���@���Farg1 �t�@�C���p�X
// �߂�l�FSoundBuffer
// �ځ@�ׁF
//****************************************************************************
bool ResourceManager::LoadFontFromTTF(const std::string& file)
{
	// ���C�u�����̏�����
	FT_Library ft;
	if(FT_Init_FreeType(&ft)){
		std::cerr << "Failed to Initialize FreeType." << std::endl;
		return false;
	}

	// �t�H���g�t�@�C���̓ǂݍ���
	FT_Face face;
	if(FT_New_Face(ft, file.c_str(), 0, &face)){
		std::cerr << "Failed to load font." << std::endl;
		return false;
	}else{
		mNowFont = file;

		// �r�b�g�}�b�v�t�H���g�̃T�C�Y���w��
		// TODO�F32�Œ�
		FT_Set_Pixel_Sizes(face, 0, 32);

		// TODO�FASCII����(128������)�Ή�
		// �Ђ炪�ȁE�J�^�J�i�͖��Ή�
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

	// freetype�̊J��
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	return true;
}

//****************************************************************************
// �֐����FGetFont
// �T�@�v�F�t�H���g�擾
// ���@���Farg1 ����
// �߂�l�F�e�N�X�`���Aoffset�A���������̃I�t�Z�b�g
// �ځ@�ׁF
//****************************************************************************
std::tuple<std::shared_ptr<Texture>, Vector3, Vector3> ResourceManager::GetFont(char c)
{
	auto iter = mCacheFonts[mNowFont].find(c);
	if(iter != mCacheFonts[mNowFont].end()){ return iter->second; }

	return std::make_tuple(nullptr, Vector3(), Vector3());
}

} // namespace tkl