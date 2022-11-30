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
		unsigned char riff[4];	// RIFFヘッダ
		unsigned int fileSize;	// ファイルサイズ
		unsigned char wave[4];	// WAVEヘッダ
	};

	struct ChunkTag
	{
		unsigned char fmt[4];
		unsigned int fmtSize;
	};

	struct FmtChank
	{
		unsigned short formatID;		// フォーマットID
		unsigned short channels;		// チャンネル数
		unsigned int samplingRate;		// サンプリング周波数(Hz)
		unsigned int bytesPerSec;		// データ速度(Bytes/Sec)
		unsigned short blockSize;		// ブロックサイズ
		unsigned short bitsPerSec;		// サンプルあたりのビット数
	};

	static bool ReadChunk();
};

using SoundInfo = tkl::SoundParser::SoundInfo;

} // namespace tkl