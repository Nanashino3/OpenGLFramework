#ifndef _SOUND_H_
#define _SOUND_H_

#include <memory>
namespace tkl
{
class SoundBuffer;
class Sound
{
public:
	Sound();
	~Sound();
	
	void Play();
	void Stop();
	bool IsPlay();

	void SetBuffer(std::shared_ptr<SoundBuffer> buffer){ mBuffer = buffer; }

	static std::shared_ptr<Sound> CreateSound(const char* filename);
private:
	unsigned int mSource;
	std::shared_ptr<SoundBuffer> mBuffer;
};

} // namespace tkl

#endif