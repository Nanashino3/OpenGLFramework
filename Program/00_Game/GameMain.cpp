#include "GameMain.h"
#include "../00_Game/GameManager.h"

#include <AL/al.h>
#include <AL/alc.h>
#include "../01_Engine/ResourceManager.h"

#pragma pack(push, 1)
struct WaveFileHeader
{
	char Riff[4];			// RIFF�w�b�_�[
	unsigned int FileSize;	// �t�@�C���T�C�Y
	char Wave[4];			// WAVE�w�b�_�[
};

struct tagChank
{
	unsigned char Fmt[4];	// fmt�`�����N
	unsigned int FmtSize;	// fmt�`�����N�̃o�C�g��
};

struct WaveFormat
{
	unsigned short FormatTag;		// �t�H�[�}�b�gID
	unsigned short Channels;		// �`�����l����
	unsigned int SamplingRate;		// �T���v�����O���[�g
	unsigned int BytesPerSec;		// �f�[�^���x(Bytes/Sec)
	unsigned short BlockAlign;		// �u���b�N�T�C�Y
	unsigned short BitsPerSample;	// �T���v��������̃r�b�g��
};
#pragma pack(pop)

bool ReadFmtChunk(FILE* fp, WaveFormat* waveFmtPcm)
{
	if(fread(waveFmtPcm, sizeof(WaveFormat), 1, fp) != 1) return false;

	printf("�f�[�^�`���F%u(1 = PCM)\n", waveFmtPcm->FormatTag);
	printf("�`�����l�����F%u\n", waveFmtPcm->Channels);
	printf("�T���v�����O���g���F%lu[Hz]\n", waveFmtPcm->SamplingRate);
	printf("�o�C�g��/���F%lu[bytes/sec]\n", waveFmtPcm->BytesPerSec);
	printf("�o�C�g���~�`�����l�����F%u[bytes]\n", waveFmtPcm->BlockAlign);
	printf("�r�b�g��/�T���v���F%u[bits/sample]\n", waveFmtPcm->BitsPerSample);

	return true;
}

bool WaveHeaderRead(const char* filename)
{
	WaveFileHeader fileHeader;
	WaveFormat fmtPcm;
	tagChank chank;
	long fPos, length;
	FILE* fp;
//	errno_t error;

	if(fopen_s(&fp, filename, "rb") != 0){
		return false;
	}
	printf("\"%s\"\n", filename);

	// �w�b�_���
	if(fread(&fileHeader, sizeof(fileHeader), 1, fp) != 1){
		fclose(fp);
		return false;
	}
	if(strncmp(fileHeader.Riff, "RIFF", 4) != 0){
		fclose(fp);
		return false;
	}

	// WAVE�w�b�_���
	if(memcmp(fileHeader.Wave, "WAVE", 4) != 0){
		fclose(fp);
		return false;
	}

	length = fileHeader.FileSize;

	// �`�����N���
	while(fread(&chank, sizeof(chank), 1, fp) == 1)
	{
		if(memcmp(chank.Fmt, "fmt ", sizeof(chank.Fmt)) == 0){
			length = chank.FmtSize;
			printf("\"fmt\"�̒����F%ld[bytes]\n\n", length);
			fPos = ftell(fp);
			if(!ReadFmtChunk(fp, &fmtPcm)) return false;
			fseek(fp, fPos + length, SEEK_SET);
		}else if(memcmp(chank.Fmt, "data", 4) == 0){
			length = chank.FmtSize;
			printf("\"data\"�̒����F%ld[bytes]\n\n", length);
			fPos = ftell(fp);
			fseek(fp, length + fPos - 4, SEEK_SET);
			break;
		}else{
			length = chank.FmtSize;
			printf("\"%c%c%c%c\"�̒����F%ld[bytes]\n\n", chank.Fmt[0], chank.Fmt[1], chank.Fmt[2], chank.Fmt[3], length);
			fPos = ftell(fp);
			fseek(fp, length + fPos - 4, SEEK_SET);
			break;
		}
	}

	fclose(fp);
	return true;
}

#define _USE_MATH_DEFINES
#include <array>
#include <cmath>
#include <thread>
bool init = false;
void GameMain(float deltaTime)
{
//	GameManager* manager = GameManager::GetInstance();
//	manager->Update(deltaTime);
	if(!init){
//		WaveHeaderRead("Resource/test_se.wav");
//		WaveHeaderRead("Resource/spell.ogg");
		WaveHeaderRead("Resource/test_bgm.wav");
		
		tkl::ResourceManager::GetInstance()->CreateSoundFromFile("Resource/test_bgm.wav");
//		tkl::ResourceManager::GetInstance()->CreateSoundFromFile("Resource/test_se.wav");
		init = true;
	}
}

void GameEnd()
{
	GameManager* manager = GameManager::GetInstance();
	manager->DestoryInstance();
}