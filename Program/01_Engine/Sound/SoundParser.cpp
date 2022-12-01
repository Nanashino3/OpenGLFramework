#include "SoundParser.h"

#include <iostream>
#include <AL/al.h>

namespace tkl
{
void SoundParser::PrintFmtChunk(const FmtChunk& fmtChunk)
{
	printf("�f�[�^�`���F%u(1 = PCM)\n", fmtChunk.formatID);
	printf("�`�����l�����F%u\n", fmtChunk.channels);
	printf("�T���v�����O���g���F%lu[Hz]\n", fmtChunk.samplingRate);
	printf("�o�C�g��/���F%lu[bytes/sec]\n", fmtChunk.bytesPerSec);
	printf("�o�C�g���~�`�����l�����F%u[bytes]\n", fmtChunk.blockSize);
	printf("�r�b�g��/�T���v���F%u[bits/sample]\n", fmtChunk.bitsPerSec);
}

bool SoundParser::LoadAudio(const char* filename, SoundInfo& sndInfo)
{
	FILE* fp;
	errno_t errNo = fopen_s(&fp, filename, "rb");
	if (errNo != 0) {
		std::cerr << "Failed to open file " << filename << std::endl;
		return false;
	}
	
	// RIFF���ʎq
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

	// �`�����N���
	ChunkTag chunkTag;
	while(fread(&chunkTag, sizeof(ChunkTag), 1, fp) == 1){
		long pos = ftell(fp);
		if(memcmp(chunkTag.fmt, "fmt ", 4) == 0){
			FmtChunk fmtChank;
			fread(&fmtChank, sizeof(FmtChunk), 1, fp);
#if 0
			PrintFmtChunk(fmtChank);
#endif		
			sndInfo.frequency = fmtChank.samplingRate;
			if(fmtChank.channels == 1){
				sndInfo.format = AL_FORMAT_MONO16;
			}else if(fmtChank.channels == 2){
				sndInfo.format = AL_FORMAT_STEREO16;
			}
		}else if(memcmp(chunkTag.fmt, "data", 4) == 0){
			sndInfo.size = chunkTag.fmtSize;
			sndInfo.data = new char[chunkTag.fmtSize];
			fread(sndInfo.data, chunkTag.fmtSize, 1, fp);
			break;
		}
		fseek(fp, chunkTag.fmtSize + pos, SEEK_SET);
	}
	fclose(fp);

	return true;
}

} // namespace tkl