#include "SoundBuffer.h"

#include <AL/al.h>

namespace tkl
{
SoundBuffer::SoundBuffer(int format, const void* data, int size, int frequency)
{
	alGenBuffers(1, &mBufferID);
	alBufferData(mBufferID, format, data, size, frequency);
}

SoundBuffer::~SoundBuffer()
{}

void SoundBuffer::Active(unsigned int source)
{
	alSourcei(source, AL_BUFFER, mBufferID);
}

} // namespace tkl