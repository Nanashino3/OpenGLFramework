#include "PlayScene.h"

#include "../../01_Engine/System.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/Camera/PostureControlCamera.h"
#include "../../01_Engine/Font.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Intersect.h"
#include "../../02_Library/Math.h"
#include "../../02_Library/Input.h"

int gMap[5][5] = {
	{ S, N, B, N, N },
	{ N, N, B, G, N },
	{ N, N, B, B, N },
	{ N, N, N, N, N },
	{ N, N, N, N, N }
};

PlayScene::PlayScene()
: mScreenW(0), mScreenH(0)
{
	tkl::System::GetInstance()->GetWindowSize(&mScreenW, &mScreenH);

	// 3Dカメラ生成
	mCamera = std::make_shared<tkl::PostureControlCamera>(mScreenW, mScreenH);
	mCamera->SetPosition(tkl::Vector3(100, 100, 300));

	// グリッド生成
	mGrid = tkl::Mesh::CreateGround(25, 5);

	// カーソル生成
	mCursor = tkl::Mesh::CreatePlane(25);
	mCursor->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test2.bmp"));
	mCursor->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));

	// フィールド生成
	std::vector<Field> fields;
	for(int i  = 0; i < 5; ++i){
		fields.clear();
		for(int j = 0; j < 5; ++j){
			tkl::Vector3 pos = tkl::Vector3(-50 + 25 * j, 0, -50 + 25 * i);
			Field field = { pos, nullptr };
			fields.emplace_back(field);
		}
		mFields.emplace_back(fields);
	}
}

PlayScene::~PlayScene()
{}

std::shared_ptr<BaseScene> PlayScene::Update(float deltaTime)
{
	std::shared_ptr<BaseScene> nextScene = shared_from_this();

	mCamera->Update();
	tkl::Font::DrawStringEx(0, 0, "プレイシーン");

	// マウス座標を元にレイを飛ばす
	int mousePosX = 0, mousePosY = 0;
	tkl::Input::GetMousePoint(&mousePosX, &mousePosY);
	tkl::Vector3 ray = tkl::Vector3::CreateScreenRay(mousePosX, mousePosY, 
		mScreenW, mScreenH, mCamera->GetView(), mCamera->GetProjection());

	// レイと平面の当たり判定
	tkl::Vector3 hit;
	if(tkl::IsIntersectLinePlane(mCamera->GetPosition(), mCamera->GetPosition() + ray * 1000.0f,
		{1, 0, 0}, tkl::Vector3::UNITY, &hit))
	{
		tkl::Font::DrawStringEx(0, 30, "PosX : %f, PosY : %f, PosZ : %f", hit.mX, hit.mY, hit.mZ);

		PriDrawSelectField(hit);
		if (tkl::Input::IsMouseDownTrigger(eMouse::MOUSE_LEFT)) {
			// 障害物の生成
		}
	}

	mGrid->Draw(mCamera);

	return nextScene;
}

// 選択しているフィールドを描画
void PlayScene::PriDrawSelectField(const tkl::Vector3& pos)
{
	for(int h = 0; h < mFields.size(); ++h){
		for(int w = 0; w < mFields[h].size(); ++w){
			tkl::Vector3 fieldPos = mFields[h][w].pos;

			if(!tkl::IsIntersectPointRect(pos.mX, pos.mZ, fieldPos.mX, fieldPos.mZ, 25)){ continue; }

			mCursor->SetPosition(fieldPos);
			mCursor->Draw(mCamera);
		}
	}
}