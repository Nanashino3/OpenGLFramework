#include "PlayScene.h"

#include "../../01_Engine/System.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/Camera/PostureControlCamera.h"
#include "../../01_Engine/Font.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Intersect.h"
#include "../../02_Library/Math.h"
#include "../../02_Library/Input.h"
#include "../../02_Library/Utility.h"

#include "../GameObject/AdvanceUnit.h"

const int SIZE = 50;
const int DIV = 5;

PlayScene::PlayScene()
: mScreenW(0), mScreenH(0)
, mFirstPosX(0), mFirstPosZ(0)
, mCamera(nullptr), mCursor(nullptr)
, mMode(MODE::EDIT_MODE)
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
	std::vector<std::vector<std::string>> map = tkl::LoadCsv("Resource/test.csv");
	for(int i  = 0; i < map.size(); ++i){
		std::vector<tkl::CELL> fields;
		for(int j = 0; j < map[i].size(); ++j){
			fields.emplace_back(tkl::CELL(i, j, static_cast<tkl::STATUS>(std::stoi(map[i][j]))));
		}
		mFields.emplace_back(fields);
	}
	
	// 経路検索(初期)
	tkl::Algorithm::RouteSearch(DIV, DIV, mFields, mRoute);
	mRouteCount = mRoute.size() - 1;

	mFirstPosX = -SIZE * DIV * 0.5f + (SIZE >> 1);
	mFirstPosZ = mFirstPosX;

	// 進軍ユニットを生成
	std::shared_ptr<AdvanceUnit> unit = std::make_shared<AdvanceUnit>(SIZE, DIV, mRoute);
	mAdvanceList.emplace_back(unit);
}

PlayScene::~PlayScene()
{}

std::shared_ptr<BaseScene> PlayScene::Update(float deltaTime)
{
	std::shared_ptr<BaseScene> nextScene = shared_from_this();

	mCamera->Update();

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
		PriDrawSelectField(hit);
	}

	//******************************************************************
	// TODO：最短経路表示用(デバッグとして呼び出したい)
	for(int i = 0; i < mRoute.size(); ++i){
		std::shared_ptr<tkl::Mesh> mesh = tkl::Mesh::CreatePlane(SIZE);

		float posX = mFirstPosX + SIZE * mRoute[i].column;
		float posZ = mFirstPosZ + SIZE * mRoute[i].row;
		mesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test.jpg"));
		mesh->SetPosition(tkl::Vector3(posX, 0, posZ));
		mesh->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));
		mesh->Draw(mCamera);
	}
	
	//******************************************************************
	// モード変更
	if(tkl::Input::IsKeyDownTrigger(eKeys::KB_ENTER)) mMode = MODE::PLAY_MODE;

	std::string str = (mMode == MODE::PLAY_MODE) ? "プレイモード" : "エディットモード";
	tkl::Font::DrawStringEx(0, 0, str.c_str());

	if(mMode == MODE::PLAY_MODE){
		for(auto iter = mAdvanceList.begin(); iter != mAdvanceList.end(); ++iter){
			(*iter)->Move(deltaTime);
		}
	}
	for (auto iter = mAdvanceList.begin(); iter != mAdvanceList.end(); ++iter) {
		(*iter)->Draw(mCamera);
	}


	//******************************************************************
	// 障害物の描画
	for(int i = 0; i < mObstacles.size(); ++i){
		mObstacles[i]->Draw(mCamera);
	}

	mGrid->Draw(mCamera);

	return nextScene;
}

// 選択しているフィールドを描画
void PlayScene::PriDrawSelectField(const tkl::Vector3& pos)
{
	if(mMode == MODE::PLAY_MODE){ return; }

	for(int h = 0; h < mFields.size(); ++h){
		for(int w = 0; w < mFields[h].size(); ++w){
			float posX = mFirstPosX + SIZE * w;
			float posZ = mFirstPosZ + SIZE * h;
			if(!tkl::IsIntersectPointRect(pos.mX, pos.mZ, posX, posZ, SIZE)){ continue; }

			if(mFields[h][w].status != tkl::STATUS::EDITABLE){ continue; }

			mCursor->SetPosition(tkl::Vector3(posX, 0, posZ));
			mCursor->Draw(mCamera);

			if(tkl::Input::IsMouseDownTrigger(eMouse::MOUSE_LEFT)){
				// 障害物の生成
				std::shared_ptr<tkl::Mesh> obstacle = tkl::Mesh::CreateBox(SIZE >> 1);
				obstacle->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/saikoro_image.png"));
				obstacle->SetPosition(tkl::Vector3(posX, 12.5f, posZ));
				mObstacles.emplace_back(obstacle);

				// 経路再探索
				int prevSize = mRoute.size();
				mFields[h][w].status = tkl::STATUS::UNIT;
//				tkl::Algorithm::RouteSearch(DIV, DIV, mFields, mRoute);

//				int newSize = mRoute.size();
//				mRouteCount = mRouteCount + abs(prevSize - newSize);
			}
		}
	}
}