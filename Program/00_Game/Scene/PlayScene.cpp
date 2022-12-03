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

const int SIZE = 50;
const int DIV = 5;

std::shared_ptr<tkl::Mesh> gMesh;

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


	std::vector<std::vector<std::string>> map = tkl::LoadCsv("Resource/test.csv");
	// フィールド生成
	for(int i  = 0; i < DIV; ++i){
		std::vector<CELL> fields;
		for(int j = 0; j < DIV; ++j){
			fields.emplace_back(CELL(i, j, static_cast<STATUS>(std::stoi(map[i][j]))));
		}
		mFields.emplace_back(fields);
	}
	
	// 経路検索(初期)
	tkl::Algorithm::RouteSearch(DIV, DIV, mFields, mRoute);
	mRouteCount = mRoute.size() - 1;

	mFirstPosX = -SIZE * DIV * 0.5f + (SIZE >> 1);
	mFirstPosZ = mFirstPosX;

	// 球体の生成
	gMesh = tkl::Mesh::CreateSphere((SIZE >> 1), 24, 16);
	gMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test.jpg"));
	float posX = mFirstPosX + SIZE * mRoute[mRouteCount].column;
	float posZ = mFirstPosZ + SIZE * mRoute[mRouteCount].row;
	gMesh->SetPosition(tkl::Vector3(posX, (SIZE >> 1), posZ));
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
	// 探索した経路を進む処理
	if(tkl::Input::IsKeyDownTrigger(eKeys::KB_ENTER)) mMode = MODE::PLAY_MODE;
	if(mMode == MODE::PLAY_MODE){
		tkl::Font::DrawStringEx(0, 0, "プレイモード");
		tkl::Vector3 pos = gMesh->GetPosition();
		float targetPosX = mFirstPosX + SIZE * mRoute[mRouteCount - 1].column;
		float targetPosZ = mFirstPosZ + SIZE * mRoute[mRouteCount - 1].row;

		// 移動量計算
		int dx = mRoute[mRouteCount - 1].column - mRoute[mRouteCount].column;
		int dz = mRoute[mRouteCount - 1].row - mRoute[mRouteCount].row;

		pos.mX += 0.5f * dx * deltaTime;
		pos.mZ += 0.5f * dz * deltaTime;

		if(dx > 0 || dz > 0){
			if(pos.mX > targetPosX || pos.mZ > targetPosZ){
				pos.mX = targetPosX; pos.mZ = targetPosZ;
				if(mRouteCount > 1) mRouteCount--;
			}
		}else if(dx < 0 || dz < 0){
			if(pos.mX < targetPosX || pos.mZ < targetPosZ){
				pos.mX = targetPosX; pos.mZ = targetPosZ;
				if(mRouteCount > 1) mRouteCount--;
			}
		}

		gMesh->SetPosition(pos);
	}else{
		tkl::Font::DrawStringEx(0, 0, "エディットモード");
	}
	gMesh->Draw(mCamera);

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

			mCursor->SetPosition(tkl::Vector3(posX, 0, posZ));
			mCursor->Draw(mCamera);

			if(tkl::Input::IsMouseDownTrigger(eMouse::MOUSE_LEFT)){
				// 障害物の生成
				std::shared_ptr<tkl::Mesh> obstacle = tkl::Mesh::CreateBox(SIZE);
				obstacle->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/saikoro_image.png"));
				obstacle->SetPosition(tkl::Vector3(posX, (SIZE >> 1), posZ));
				mObstacles.emplace_back(obstacle);

				// 経路再探索
				int prevSize = mRoute.size();
				mFields[h][w].status = STATUS::OBSTACLE;
				tkl::Algorithm::RouteSearch(DIV, DIV, mFields, mRoute);

				int newSize = mRoute.size();
				mRouteCount = mRouteCount + abs(prevSize - newSize);
			}
		}
	}
}