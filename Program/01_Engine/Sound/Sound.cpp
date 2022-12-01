#include "Sound.h"

#include <AL/al.h>
#include "SoundBuffer.h"
#include "../../01_Engine/ResourceManager.h"

namespace tkl
{
Sound::Sound()
: mSource(0)
, mBuffer(nullptr)
{}

Sound::~Sound()
{}

void Sound::Play()
{
	mBuffer->Active(mSource);
	alSourcePlay(mSource);
}

void Sound::Stop()
{}

std::shared_ptr<Sound> Sound::CreateSound(const char* filename)
{
	std::shared_ptr<Sound> sound = std::make_shared<Sound>();
	sound->SetBuffer(tkl::ResourceManager::GetInstance()->CreateSoundFromFile(filename));

	alGenSources(1, &sound->mSource);
	return sound;
}

} // namespace tkl