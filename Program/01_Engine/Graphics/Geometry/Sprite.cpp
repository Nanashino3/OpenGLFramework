//****************************************************************************
// ファイル名：Sprite
// 作　成　日：2023/3/7
#include "Sprite.h"

#include "Material.h"
#include "Texture.h"
#include "VertexArray.h"
#include "../Renderer/SpriteRenderer.h"
#include "../../ResourceManager.h"

static constexpr int VERTEX_NUM = 4;

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
	mVertexArray = std::make_shared<VertexArray>(VERTEX_NUM, vertices, indicesNum, indices);

	mScale = tkl::Vector3(mSpriteWidth, mSpriteHeight, 0.0f);
}

Sprite::~Sprite()
{}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：なし
// 戻り値：なし
// 詳　細：登録した画像のUV座標を計算し直し更新する
//****************************************************************************
void Sprite::Update(float deltaTime)
{
	if(!mIsAnimation){ return; }

	mElapsedTime += deltaTime;
	if(mElapsedTime >= mAnimInterval){
		mElapsedTime = 0;

		// フレーム毎のUV座標を計算
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

		// 最新のUV座標で更新
		for(int i = 0; i < VERTEX_NUM; i++){
			mVertexArray->UpdateUVCoords(i, uv[i][0], uv[i][1]);
		}

		// アニメーションのフレームを計算
		mCurrentFrame = (mCurrentFrame + 1) % mTotalFrames;
	}
}

} // namespace tklc