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
#include "../GameObject/DefenseUnit.h"

const int SIZE = 50;
const int DIV = 5;
const int CREATE_MAX = 5;

PlayScene::PlayScene()
: mScreenW(0), mScreenH(0)
, mFirstPosX(0), mFirstPosZ(0)
, mCamera(nullptr), mCursor(nullptr)
, mElapsed(0)
, mMapRow(1), mMapColumn(1)
{
	tkl::System::GetInstance()->GetWindowSize(&mScreenW, &mScreenH);

	// 3Dカメラ生成
	mCamera = std::make_shared<tkl::PostureControlCamera>(mScreenW, mScreenH);
	mCamera->SetPosition(tkl::Vector3(0, 100, 300));

	// グリッド生成
	mGrid = tkl::Mesh::CreateGround(SIZE, DIV);

	// カーソル生成
	mCursor = tkl::Mesh::CreatePlane(SIZE);
	mCursor->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test2.bmp"));
	mCursor->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));

	// フィールド生成
	std::vector<std::vector<std::string>> map = tkl::LoadCsv("Resource/test.csv");
	mMapRow = map.size();
	mMapColumn = map[0].size();

	for(int i = 0; i < map.size(); ++i){
		std::vector<tkl::CELL> fields;
		for(int j = 0; j < map[i].size(); ++j){
			fields.emplace_back(tkl::CELL(i, j, static_cast<tkl::STATUS>(std::stoi(map[i][j]))));
		}
		mFields.emplace_back(fields);
	}
	
	// 経路検索(初期)
	tkl::Algorithm::RouteSearch(mMapRow, mMapColumn, mFields, mRoute);

	mFirstPosX = -SIZE * mMapRow * 0.5f + (SIZE >> 1);
	mFirstPosZ = -SIZE * mMapColumn * 0.5f + (SIZE >> 1);
}

PlayScene::~PlayScene()
{}

std::shared_ptr<BaseScene> PlayScene::Update(float deltaTime)
{
	tkl::Font::DrawStringEx(0, 0, "プレイシーン");

	std::shared_ptr<BaseScene> nextScene = shared_from_this();

	// カメラ更新
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
		mesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/panel_concrete.bmp"));
		mesh->SetPosition(tkl::Vector3(posX, 0, posZ));
		mesh->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));
		mesh->Draw(mCamera);
	}
	
	//******************************************************************
	// 進軍ユニット
	// TODO：進軍ユニット管理者を作ったほうがいい？
	mElapsed += deltaTime;

	tkl::Font::DrawStringEx(0, 50, "DeltaTIme：%f", deltaTime);
	if (mElapsed > 5.0f){
		mElapsed = 0;

		// 新しい進軍ユニットを生成
		std::shared_ptr<AdvanceUnit> unit = std::make_shared<AdvanceUnit>(SIZE, mMapRow, mMapColumn, mRoute);
		mAdvanceList.emplace_back(unit);
	}

	for (auto iter = mAdvanceList.begin(); iter != mAdvanceList.end();) {
		(*iter)->SetNewRoute(mRoute);
		(*iter)->Move(deltaTime);
		(*iter)->Draw(mCamera);
		if((*iter)->IsTargetPoint()){ iter = mAdvanceList.erase(iter); continue; }
		++iter;
	}

	//******************************************************************
	// 防衛ユニット
	for(auto unit : mDefenseList){
		unit->Update(deltaTime, mCamera);
	}

	mGrid->Draw(mCamera);

	return nextScene;
}

// 選択しているフィールドを描画
void PlayScene::PriDrawSelectField(const tkl::Vector3& pos)
{
	for(int h = 0; h < mFields.size(); ++h){
		for(int w = 0; w < mFields[h].size(); ++w){
			float posX = mFirstPosX + SIZE * w;
			float posZ = mFirstPosZ + SIZE * h;
			if(!tkl::IsIntersectPointRect(pos.mX, pos.mZ, posX, posZ, SIZE)){ continue; }

			if(mFields[h][w].status != tkl::STATUS::EDITABLE){ continue; }

			mCursor->SetPosition(tkl::Vector3(posX, 0, posZ));
			mCursor->Draw(mCamera);

			if(tkl::Input::IsMouseDownTrigger(eMouse::MOUSE_LEFT)){
				mFields[h][w].status = tkl::STATUS::UNIT;

				// 経路再探索
				std::vector<tkl::CELL> newRoute;
				if(!tkl::Algorithm::RouteSearch(DIV, DIV, mFields, newRoute)){
					mFields[h][w].status = tkl::STATUS::EDITABLE;
					continue;
				}
				mRoute = newRoute;

				// 防衛ユニット生成
				std::shared_ptr<DefenseUnit> unit = std::make_shared<DefenseUnit>(tkl::Vector3(posX, 0, posZ));
				mDefenseList.emplace_back(unit);
			}
		}
	}
}