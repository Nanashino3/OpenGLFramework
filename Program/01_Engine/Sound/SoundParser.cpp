#include "SoundParser.h"

#include <algorithm>
#include <iostream>
#include <AL/al.h>

namespace tkl
{
void SoundParser::PrintFmtChunk(const WAVEFORMATEX& waveFormTex)
{
	printf("データ形式：%u(1 = PCM)\n", waveFormTex.formatTag);
	printf("チャンネル数：%u\n", waveFormTex.channels);
	printf("サンプリング周波数：%lu[Hz]\n", waveFormTex.samplesPerSec);
	printf("バイト数/数：%lu[bytes/sec]\n", waveFormTex.avgBytesPerSec);
	printf("バイト数×チャンネル数：%u[bytes]\n", waveFormTex.blockAlign);
	printf("ビット数/サンプル：%u[bits/sample]\n", waveFormTex.bitsPerSample);
	printf("拡張データサイズ：%u\n", waveFormTex.cbSize);
}

bool SoundParser::LoadAudio(const char* filename, SoundInfo& sndInfo)
{
	FILE* fp;
	errno_t errNo = fopen_s(&fp, filename, "rb");
	if (errNo != 0) {
		std::cerr << "Failed to open file " << filename << std::endl;
		return false;
	}
	
	// RIFF識別子
	Header header;
	if(fread(&header, sizeof(Header), 1, fp) != 1){
		std::cerr << "Failed to read header." << std::endl;
		fclose(fp);
		return false;
	}
	if(memcmp(header.riff, "RIFF", 4) != 0){
		fclose(fp);
		return false;
	}
	if(memcmp(header.wave, "WAVE", 4) != 0){
		fclose(fp);
		return false;
	}

	// チャンク情報
	ChunkTag chunkTag;
	while(fread(&chunkTag, sizeof(ChunkTag), 1, fp) == 1){
		long pos = ftell(fp);
		if(memcmp(chunkTag.fmt, "fmt ", 4) == 0){
			WAVEFORMATEX waveForm;
			fread(&waveForm, sizeof(WAVEFORMATEX), 1, fp);

//			PrintFmtChunk(waveForm);

			sndInfo.frequency = waveForm.samplesPerSec;
			if(waveForm.channels == 1){
				sndInfo.format = AL_FORMAT_MONO16;
			}else if(waveForm.channels == 2){
				sndInfo.format = AL_FORMAT_STEREO16;
			}
		}else if(memcmp(chunkTag.fmt, "data", 4) == 0){
			sndInfo.size = chunkTag.fmtSize;
			sndInfo.data = new char[chunkTag.fmtSize];
			fread(sndInfo.data, chunkTag.fmtSize, 1, fp);

//			printf("dataの長さ : %d\n\n", chunkTag.fmtSize);

			break;
		}
		fseek(fp, chunkTag.fmtSize + pos, SEEK_SET);
	}
	fclose(fp);

	return true;
}

} // namespace tkl