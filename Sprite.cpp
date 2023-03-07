#include "Sprite.h"


#include "Program/01_Engine/Graphics/Renderer/SpriteRenderer.h"
#include "Program/01_Engine/Graphics/Geometry/VertexArray.h"
#include "Program/01_Engine/Graphics/Geometry/Material.h"
#include "Program/01_Engine/ResourceManager.h"

namespace tkl
{
Sprite::Sprite(const char* file, int totalFrames)
: mElapsedTime(0.0f)
, mTotalFrames(totalFrames)
, mCurrentFrame(0.0f) 
{
	mTexture = ResourceManager::GetInstance()->CreateTextureFromFile(file);

	mRenderer = std::make_shared<SpriteRenderer>("Sprite");
	mMaterial = std::make_shared<Material>();

	VertexArray::VERTEX vertices[] = {
		{-0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f,  0.0f},
		{ 0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f,  0.0f},
		{ 0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f,  1.0f},
		{-0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f,  1.0f}
	};

	int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	int indicesNum = sizeof(indices) / sizeof(indices[0]);
	mVertexArray = std::make_shared<VertexArray>(4, vertices, indicesNum, indices);
}

Sprite::~Sprite()
{}

void Sprite::Update(float deltaTime)
{
	// アニメーションのフレームを計算
	mElapsedTime += deltaTime;
	if(mElapsedTime >= 0.05f){
		mElapsedTime = 0;

		float u0 = fmodf(mCurrentFrame, 8) * 0.125f;
		float u1 = u0 + 0.125f;
		float v0 = floorf(mCurrentFrame / 8) * 0.5f;
		float v1 = v0 + 0.5f;

		mCurrentFrame = (mCurrentFrame + 1) % mTotalFrames;
		float uv[][2] = {
			{u0, v0},
			{u1, v0},
			{u1, v1},
			{u0, v1}
		};

		for(int i = 0; i < 4; i++){
			mVertexArray->UpdateUVCoords(i, uv[i][0], uv[i][1]);
		}
	}
}

} // namespace tklc