#pragma once

namespace tkl
{
class SoundParser
{
public:
	struct SoundInfo
	{
		int format;
		char* data;
		int size;
		int frequency;
	};
	static bool LoadAudio(const char* filename, SoundInfo& sndInfo);

private:
	struct Header
	{
		unsigned char riff[4];	// RIFF�w�b�_
		unsigned int fileSize;	// �t�@�C���T�C�Y
		unsigned char wave[4];	// WAVE�w�b�_
	};

	struct ChunkTag
	{
		unsigned char fmt[4];
		unsigned int fmtSize;
	};

	struct FmtChank
	{
		unsigned short formatID;		// �t�H�[�}�b�gID
		unsigned short channels;		// �`�����l����
		unsigned int samplingRate;		// �T���v�����O���g��(Hz)
		unsigned int bytesPerSec;		// �f�[�^���x(Bytes/Sec)
		unsigned short blockSize;		// �u���b�N�T�C�Y
		unsigned short bitsPerSec;		// �T���v��������̃r�b�g��
	};

	static bool ReadChunk();
};

using SoundInfo = tkl::SoundParser::SoundInfo;

} // namespace tkl