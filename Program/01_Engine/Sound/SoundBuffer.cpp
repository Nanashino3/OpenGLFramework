#include "SoundBuffer.h"

#include <AL/al.h>
SoundBuffer::SoundBuffer()
{
	alGenBuffers(1, &mBufferID);
//	alBufferData(mBufferID, format, &data[0], data.size() * sizeof(ALshort), );
}

SoundBuffer::~SoundBuffer()
{}