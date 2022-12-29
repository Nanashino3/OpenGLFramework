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
		char riff[4];	// RIFFヘッダ
		int fileSize;	// ファイルサイズ
		char wave[4];	// WAVEヘッダ
	};

	struct ChunkTag
	{
		char fmt[4];
		int fmtSize;
	};

	struct WAVEFORMATEX {
		unsigned short formatTag;		// フォーマットタイプ
		unsigned short channels;		// チャンネル数
		unsigned long samplesPerSec;	// サンプルレート(Hz)
		unsigned long avgBytesPerSec;	// 平均データ転送レート(バイト/秒)
		unsigned short blockAlign;		// ブロックアラインメント(バイト)
		unsigned short bitsPerSample;	// 1サンプルあたりのビット数
		unsigned short cbSize;			// 拡張データサイズ
	};
	static void PrintFmtChunk(const WAVEFORMATEX& waveFormTex);
};

using SoundInfo = tkl::SoundParser::SoundInfo;

} // namespace tkl

#endif