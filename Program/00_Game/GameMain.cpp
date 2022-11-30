#include "GameMain.h"
#include "../00_Game/GameManager.h"

#include <AL/al.h>
#include <AL/alc.h>
#include "../01_Engine/ResourceManager.h"

#pragma pack(push, 1)
struct WaveFileHeader
{
	char Riff[4];			// RIFFヘッダー
	unsigned int FileSize;	// ファイルサイズ
	char Wave[4];			// WAVEヘッダー
};

struct tagChank
{
	unsigned char Fmt[4];	// fmtチャンク
	unsigned int FmtSize;	// fmtチャンクのバイト数
};

struct WaveFormat
{
	unsigned short FormatTag;		// フォーマットID
	unsigned short Channels;		// チャンネル数
	unsigned int SamplingRate;		// サンプリングレート
	unsigned int BytesPerSec;		// データ速度(Bytes/Sec)
	unsigned short BlockAlign;		// ブロックサイズ
	unsigned short BitsPerSample;	// サンプル当たりのビット数
};
#pragma pack(pop)

bool ReadFmtChunk(FILE* fp, WaveFormat* waveFmtPcm)
{
	if(fread(waveFmtPcm, sizeof(WaveFormat), 1, fp) != 1) return false;

	printf("データ形式：%u(1 = PCM)\n", waveFmtPcm->FormatTag);
	printf("チャンネル数：%u\n", waveFmtPcm->Channels);
	printf("サンプリング周波数：%lu[Hz]\n", waveFmtPcm->SamplingRate);
	printf("バイト数/数：%lu[bytes/sec]\n", waveFmtPcm->BytesPerSec);
	printf("バイト数×チャンネル数：%u[bytes]\n", waveFmtPcm->BlockAlign);
	printf("ビット数/サンプル：%u[bits/sample]\n", waveFmtPcm->BitsPerSample);

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

	// ヘッダ情報
	if(fread(&fileHeader, sizeof(fileHeader), 1, fp) != 1){
		fclose(fp);
		return false;
	}
	if(strncmp(fileHeader.Riff, "RIFF", 4) != 0){
		fclose(fp);
		return false;
	}

	// WAVEヘッダ情報
	if(memcmp(fileHeader.Wave, "WAVE", 4) != 0){
		fclose(fp);
		return false;
	}

	length = fileHeader.FileSize;

	// チャンク情報
	while(fread(&chank, sizeof(chank), 1, fp) == 1)
	{
		if(memcmp(chank.Fmt, "fmt ", sizeof(chank.Fmt)) == 0){
			length = chank.FmtSize;
			printf("\"fmt\"の長さ：%ld[bytes]\n\n", length);
			fPos = ftell(fp);
			if(!ReadFmtChunk(fp, &fmtPcm)) return false;
			fseek(fp, fPos + length, SEEK_SET);
		}else if(memcmp(chank.Fmt, "data", 4) == 0){
			length = chank.FmtSize;
			printf("\"data\"の長さ：%ld[bytes]\n\n", length);
			fPos = ftell(fp);
			fseek(fp, length + fPos - 4, SEEK_SET);
			break;
		}else{
			length = chank.FmtSize;
			printf("\"%c%c%c%c\"の長さ：%ld[bytes]\n\n", chank.Fmt[0], chank.Fmt[1], chank.Fmt[2], chank.Fmt[3], length);
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