#pragma once

#include "../../02_Library/Vector.h"

class SoundSource
{
public:
	SoundSource();
	~SoundSource();

	void Play(unsigned int bufferID);

private:
	unsigned int mSourceID;
	float mPitch;
	float mGain;
	tkl::Vector3 mPosition;
	tkl::Vector3 mVelocity;
	bool mIsLooping;
};