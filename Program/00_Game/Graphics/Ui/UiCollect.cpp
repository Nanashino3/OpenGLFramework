#include "UiCollect.h"

#include "../../../01_Engine/System.h"
#include "../../../01_Engine/ResourceManager.h"
#include "../../../01_Engine/Camera/ScreenCamera.h"
#include "../../../01_Engine/Graphics/Font/Font.h"
#include "../../../01_Engine/Graphics/Geometry/Mesh.h"
#include "../../../01_Engine/Graphics/Geometry/Texture.h"

static constexpr const char* UI_FILE = "Resource/texture/ui/image_4.png";

UiCollect::UiCollect()
: mStartPosX(0.0f), mStartPosY(0.0f)
, mTotalCost(0)
, mMesh(nullptr)
, mCamera(nullptr)
{}

UiCollect::~UiCollect()
{}

void UiCollect::Initialize()
{
	int screenW, screenH;
	tkl::System::GetInstance()->GetWindowSize(&screenW, &screenH);
	mCamera = std::make_shared<tkl::ScreenCamera>(screenW, screenH);

	std::shared_ptr<tkl::Texture> newTex = tkl::ResourceManager::GetInstance()->CreateTextureFromFile(UI_FILE);

	mStartPosX = -screenW * 0.5f + static_cast<float>(newTex->GetWidth() * 0.5f);
	mStartPosY =  (screenH * 0.5f - static_cast<float>(newTex->GetHeight() * 0.5f)) - 60.0f;

	mMesh = tkl::Mesh::CreateMeshForSprite();
	mMesh->SetTexture(newTex);
	mMesh->SetPosition(tkl::Vector3(mStartPosX, mStartPosY, 0.0f));
}

void UiCollect::Update()
{
	mCamera->Update();
}

void UiCollect::Draw()
{
	tkl::Font::DrawStringEx(60.0f, 80.0f, tkl::Vector3(1.0f, 1.0f, 1.0f), "%d", mTotalCost);
	mMesh->Draw(mCamera);
}