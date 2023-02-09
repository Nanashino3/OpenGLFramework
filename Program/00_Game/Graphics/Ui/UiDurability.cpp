#include "UiDurability.h"

#include "../../../01_Engine/System.h"
#include "../../../01_Engine/ResourceManager.h"
#include "../../../01_Engine/Camera/ScreenCamera.h"
#include "../../../01_Engine/Graphics/Geometry/Mesh.h"
#include "../../../01_Engine/Graphics/Geometry/Texture.h"

static constexpr const char* UI_FILE = "Resource/texture/Defense_64.png";

UiDurability::UiDurability(int durability)
: mDurability(durability)
, mCamera(nullptr)
{}

UiDurability::~UiDurability()
{}

void UiDurability::Initialize()
{
	int screenW, screenH;
	tkl::System::GetInstance()->GetWindowSize(&screenW, &screenH);
	mCamera = std::make_shared<tkl::ScreenCamera>(screenW, screenH);

	// ˆê’U‚¨ŽŽ‚µ
	std::shared_ptr<tkl::Texture> newTex = tkl::ResourceManager::GetInstance()->CreateTextureFromFile(UI_FILE);

	float startPosX = -screenW * 0.5f + static_cast<float>(newTex->GetWidth() * 0.5f);
	float startPosY =  screenH * 0.5f - static_cast<float>(newTex->GetHeight() * 0.5f);
	float offsetX = static_cast<float>(newTex->GetWidth() * 0.5f) + 10.0f;
	for(int i = 0; i < mDurability; ++i){
		std::shared_ptr<tkl::Mesh> newMesh = tkl::Mesh::CreateMeshForSprite();
		newMesh->SetTexture(newTex);
		newMesh->SetPosition(tkl::Vector3(startPosX + offsetX * i, startPosY, 0.0f));

		mMeshList.emplace_back(newMesh);
	}
}

void UiDurability::Update()
{
	mCamera->Update();
	
}

void UiDurability::Draw()
{
	for(int i = 0; i < mDurability; ++i){
		mMeshList[i]->Draw(mCamera);
	}
}