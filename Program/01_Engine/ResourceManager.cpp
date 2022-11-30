#include "ResourceManager.h"

#include <SOIL.h>
#include "Texture.h"

#include "Sound/SoundParser.h"
#include <iostream>
#include <AL/al.h>

namespace tkl
{
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

// �e�N�X�`������(�t�@�C����)
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

// �T�E���h����(�t�@�C����)
void ResourceManager::CreateSoundFromFile(const char* fileName)
{
//	auto iter = mCacheSounds.find(fileName);
//	if(iter != mCacheSounds.end()){ return iter->second; }

#if 1
	// �I�[�f�B�I�����[�h
	tkl::SoundInfo sndInfo;
	tkl::SoundParser::LoadAudio(fileName, sndInfo);

	ALuint bufferID;
	alGenBuffers(1, &bufferID);

	ALuint sourceID;
	alGenSources(1, &sourceID);

	alBufferData(bufferID, sndInfo.format, &sndInfo.data[0], sndInfo.size, sndInfo.frequency);
	alSourcei(sourceID, AL_BUFFER, bufferID);
	alSourcePlay(sourceID);
#else
	FILE* fp;
	errno_t errNo = fopen_s(&fp, fileName, "rb");
	if(errNo != 0){
		std::cerr << "Failed to open file " << fileName << std::endl;
		return ;
	}

	struct FileHeader
	{
		char riff[4];			// RIFF�w�b�_
		unsigned int fileSize;	// �t�@�C���T�C�Y
		char wave[4];			// WAVE�w�b�_
	};
	FileHeader fileHeader;
	fread(&fileHeader, sizeof(FileHeader), 1, fp);

	struct ChankTag
	{
		char fmt[4];
		unsigned int fmtSize;
	};
	ChankTag tag;
	fread(&tag, sizeof(ChankTag), 1, fp);

	struct FmtChank
	{
		unsigned short formatID;		// �t�H�[�}�b�gID
		unsigned short channels;		// �`�����l����
		unsigned int samplingRate;		// �T���v�����O���g��(Hz)
		unsigned int bytesPerSec;		// �f�[�^���x(Bytes/Sec)
		unsigned short blockSize;		// �u���b�N�T�C�Y
		unsigned short bitsPerSec;		// �T���v��������̃r�b�g��
	};
	FmtChank fmtChank;
	fread(&fmtChank, sizeof(FmtChank), 1, fp);
	if(fmtChank.formatID != 1){
		unsigned short expansionSize;	// �g���p�����[�^�̃T�C�Y
		fread(&expansionSize, sizeof(unsigned short), 1, fp);

		unsigned char* expansionData;
		fread(&expansionData, sizeof(unsigned char*), 1, fp);
	}

	struct DataChank
	{
		char chankID[4];
		unsigned int waveformSize;
	};
	DataChank dataChank;
	fread(&dataChank, sizeof(DataChank), 1, fp);

	char* waveData = new char[dataChank.waveformSize];
	fread(waveData, dataChank.waveformSize, 1, fp);

	fclose(fp);

	ALuint bufferID;
	alGenBuffers(1, &bufferID);

	ALuint sourceID;
	alGenSources(1, &sourceID);

	alBufferData(bufferID, AL_FORMAT_STEREO16, &waveData[0], dataChank.waveformSize, fmtChank.samplingRate);
	alSourcei(sourceID, AL_BUFFER, bufferID);
	alSourcePlay(sourceID);
#endif

	int a = 0;
//	std::shared_ptr<SoundSource> buffer = std::make_shared<SoundSource>();
//	mCacheSounds.emplace_back(buffer);
	
}

} // namespace tkl