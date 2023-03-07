#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <memory>
#include "Program/01_Engine/Graphics/Geometry/Mesh.h"

namespace tkl
{
class Sprite : public Mesh
{
public:
	Sprite(const char* file, int totalFrames);
	virtual ~Sprite();

	void Update(float deltaTime);

	int GetTotalFrames() const { return mTotalFrames; }
	int GetCurrentFrame() const { return mCurrentFrame;}

private:
	float mElapsedTime;
	int mTotalFrames;
	int mCurrentFrame;
};

} // namespace tkl

#endif