#include "Sprite.h"

#include "Material.h"
#include "Texture.h"
#include "VertexArray.h"
#include "../Renderer/SpriteRenderer.h"
#include "../../ResourceManager.h"

namespace tkl
{
Sprite::Sprite(const char* file, int totalFrames, int colNum, int rowNum, bool isAnimation, float animInterval)
: mElapsedTime(0.0f)
, mTotalFrames(totalFrames)
, mCurrentFrame(0.0f)
, mColNum(colNum)
, mRowNum(rowNum)
, mSpriteWidth(1.0f / colNum)
, mSpriteHeight(1.0f / rowNum)
, mIsAnimation(isAnimation)
, mAnimInterval(animInterval)
{
	mTexture = ResourceManager::GetInstance()->CreateTextureFromFile(file);

	mRenderer = std::make_shared<SpriteRenderer>("Sprite");
	mMaterial = std::make_shared<Material>();

	VertexArray::VERTEX vertices[] = {
		{-0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f,			0.0f},
		{ 0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 0.0f, mSpriteWidth,  0.0f},
		{ 0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 0.0f, mSpriteWidth,  mSpriteHeight},
		{-0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f,			mSpriteHeight}
	};

	int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	int indicesNum = sizeof(indices) / sizeof(indices[0]);
	mVertexArray = std::make_shared<VertexArray>(4, vertices, indicesNum, indices);

	mScale = tkl::Vector3(mSpriteWidth, mSpriteHeight, 0.0f);
}

Sprite::~Sprite()
{}

void Sprite::Update(float deltaTime)
{
	if(!mIsAnimation){ return; }

	mElapsedTime += deltaTime;
	if(mElapsedTime >= mAnimInterval){
		mElapsedTime = 0;

		// �t���[������UV���W���v�Z
		float u0 = fmodf(mCurrentFrame, mColNum) * mSpriteWidth;
		float u1 = u0 + mSpriteWidth;
		float v0 = floorf(mCurrentFrame / mColNum) * mSpriteHeight;
		float v1 = v0 + mSpriteHeight;

		float uv[][2] = {
			{u0, v0},
			{u1, v0},
			{u1, v1},
			{u0, v1}
		};

		// �ŐV��UV���W�ōX�V(�X�v���C�g�Ȃ̂�4���_�Ō��ߑł�)
		for(int i = 0; i < 4; i++){
			mVertexArray->UpdateUVCoords(i, uv[i][0], uv[i][1]);
		}

		// �A�j���[�V�����̃t���[�����v�Z
		mCurrentFrame = (mCurrentFrame + 1) % mTotalFrames;
	}
}

} // namespace tklc