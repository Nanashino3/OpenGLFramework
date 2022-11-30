#include "SoundSource.h"

#include <AL/al.h>
SoundSource::SoundSource()
: mSourceID(0)
, mPitch(1.0f), mGain(1.0f)
, mPosition(tkl::Vector3::ZERO)
, mVelocity(tkl::Vector3::ZERO)
, mIsLooping(false)
{
	alGenSources(1, &mSourceID);
//	mSoundBuffer = std::shaerd_ptr<SoundBuffer>(mSourceID, );
}

SoundSource::~SoundSource()
{
	alDeleteSources(1, &mSourceID);
}

void SoundSource::Play(unsigned int bufferID)
{
//	mSoundBuffer->Active();
	alSourcePlay(mSourceID);
}