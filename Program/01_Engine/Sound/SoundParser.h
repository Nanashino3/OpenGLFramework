#ifndef _SOUNDPARSER_H_
#define _SOUNDPARSER_H_

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
		char riff[4];	// RIFF�w�b�_
		int fileSize;	// �t�@�C���T�C�Y
		char wave[4];	// WAVE�w�b�_
	};

	struct ChunkTag
	{
		char fmt[4];
		int fmtSize;
	};

	struct WAVEFORMATEX {
		unsigned short formatTag;		// �t�H�[�}�b�g�^�C�v
		unsigned short channels;		// �`�����l����
		unsigned long samplesPerSec;	// �T���v�����[�g(Hz)
		unsigned long avgBytesPerSec;	// ���σf�[�^�]�����[�g(�o�C�g/�b)
		unsigned short blockAlign;		// �u���b�N�A���C�������g(�o�C�g)
		unsigned short bitsPerSample;	// 1�T���v��������̃r�b�g��
		unsigned short cbSize;			// �g���f�[�^�T�C�Y
	};
	static void PrintFmtChunk(const WAVEFORMATEX& waveFormTex);
};

using SoundInfo = tkl::SoundParser::SoundInfo;

} // namespace tkl

#endif