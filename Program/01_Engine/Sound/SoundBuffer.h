#ifndef _SOUNDBUFFER_H_ 
#define _SOUNDBUFFER_H_ 

namespace tkl
{
class SoundBuffer
{
public:
	SoundBuffer(int format, const void* data, int size, int frequency);
	~SoundBuffer();

	void Active(unsigned int source);

private:
	unsigned int mBufferID;
};

} // namespace tkl

#endif