//****************************************************************************
// ファイル名：Sprite
// 作　成　日：2023/3/7
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <memory>
#include "Mesh.h"

namespace tkl
{
class Sprite : public Mesh
{
public:
	Sprite(const char* file, int totalFrames = 0, int colNum = 0, int rowNum = 0, bool isAnimation = false, float animInterval = 0.05f);
	virtual ~Sprite();

	void Update(float deltaTime);

	int GetTotalFrames() const { return mTotalFrames; }
	int GetCurrentFrame() const { return mCurrentFrame;}

private:
	float mElapsedTime;
	int mTotalFrames;
	int mCurrentFrame;

	int mColNum;
	int mRowNum;
	float mSpriteWidth;
	float mSpriteHeight;
	bool mIsAnimation;
	float mAnimInterval;
};

} // namespace tkl

#endif