#include "PlayScene.h"

#include "../../01_Engine/System.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/Camera/PostureControlCamera.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Font.h"

PlayScene::PlayScene()
{
	mPlane = tkl::Mesh::CreatePlane(50);
	mPlane->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test.jpg"));
	
	int screenW = 0, screenH = 0;
	tkl::System::GetInstance()->GetWindowSize(&screenW, &screenH);
	mCamera = std::make_shared<tkl::PostureControlCamera>(screenW, screenH);
	mCamera->SetPosition(tkl::Vector3(500, 500, 500));

	mGrid = tkl::Mesh::CreateGround(50, 20);
}

PlayScene::~PlayScene()
{}

std::shared_ptr<BaseScene> PlayScene::Update(float deltaTime)
{
	std::shared_ptr<BaseScene> nextScene = shared_from_this();

	mCamera->Update();
	mGrid->Draw(mCamera);
	mPlane->Draw(mCamera);
	tkl::Font::DrawString(0, 0, "プレイシーン");

	return nextScene;
}