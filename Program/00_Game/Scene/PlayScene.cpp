#include "PlayScene.h"

#include "../../01_Engine/System.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/Camera/PostureControlCamera.h"
#include "../../01_Engine/Font.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Intersect.h"
#include "../../02_Library/Math.h"
#include "../../02_Library/Input.h"

const int SIZE = 50;
const int DIV = 5;

STATUS map[DIV][DIV] = {
	{STATUS::START, STATUS::EMPTY, STATUS::OBSTACLE, STATUS::EMPTY,		STATUS::EMPTY},
	{STATUS::EMPTY, STATUS::EMPTY, STATUS::OBSTACLE, STATUS::GOAL,		STATUS::EMPTY},
	{STATUS::EMPTY, STATUS::EMPTY, STATUS::OBSTACLE, STATUS::OBSTACLE,	STATUS::EMPTY},
	{STATUS::EMPTY, STATUS::EMPTY, STATUS::EMPTY,	 STATUS::EMPTY,		STATUS::EMPTY},
	{STATUS::EMPTY, STATUS::EMPTY, STATUS::EMPTY,	 STATUS::EMPTY,		STATUS::EMPTY},
};

PlayScene::PlayScene()
: mScreenW(0), mScreenH(0)
{
	tkl::System::GetInstance()->GetWindowSize(&mScreenW, &mScreenH);

	// 3Dカメラ生成
	mCamera = std::make_shared<tkl::PostureControlCamera>(mScreenW, mScreenH);
	mCamera->SetPosition(tkl::Vector3(100, 100, 300));

	// グリッド生成
	mGrid = tkl::Mesh::CreateGround(SIZE, DIV);

	// カーソル生成
	mCursor = tkl::Mesh::CreatePlane(SIZE);
	mCursor->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test2.bmp"));
	mCursor->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));

	// フィールド生成
//	float firstPosX = -SIZE * DIV * 0.5f + (SIZE >> 1);
//	float firstPosZ = firstPosX;
	for(int i  = 0; i < DIV; ++i){
		std::vector<CELL> fields;
		for(int j = 0; j < DIV; ++j){
			CELL cell = CELL(i, j, map[i][j]);
//			tkl::Vector3 pos = tkl::Vector3(firstPosX + SIZE * j, 0, firstPosZ + SIZE * i);	
//			Field field = { pos, CELL(i, j, map[i][j]) };
			fields.emplace_back(cell);
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
	std::vector<CELL> route;
	if(tkl::IsIntersectLinePlane(mCamera->GetPosition(), mCamera->GetPosition() + ray * 1000.0f,
		{1, 0, 0}, tkl::Vector3::UNITY, &hit))
	{
		PriDrawSelectField(hit);
		if (tkl::Input::IsMouseDownTrigger(eMouse::MOUSE_LEFT)) {
			// 障害物の生成
			
			// 経路探索
			tkl::Algorithm::RouteSearch(DIV, DIV, mFields, route);
			int a = 0;
		}
	}

	mGrid->Draw(mCamera);

	return nextScene;
}

// 選択しているフィールドを描画
void PlayScene::PriDrawSelectField(const tkl::Vector3& pos)
{
	float firstPosX = -SIZE * DIV * 0.5f + (SIZE >> 1);
	float firstPosZ = firstPosX;
	for(int h = 0; h < mFields.size(); ++h){
		for(int w = 0; w < mFields[h].size(); ++w){
//			tkl::Vector3 fieldPos = mFields[h][w].pos;
			float posX = firstPosX + SIZE * w;
			float posZ = firstPosZ + SIZE * h;
			if(!tkl::IsIntersectPointRect(pos.mX, pos.mZ, posX, posZ, SIZE)){ continue; }

			mCursor->SetPosition(tkl::Vector3(posX, 0, posZ));
			mCursor->Draw(mCamera);
		}
	}
}