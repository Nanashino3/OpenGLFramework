#include "PlayScene.h"

#include "../../01_Engine/System.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/Camera/PostureControlCamera.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Font.h"
#include "../../01_Engine/Intersect.h"
#include "../../02_Library/Math.h"
#include "../../02_Library/Input.h"

PlayScene::PlayScene()
: mScreenW(0), mScreenH(0)
{
	// フィールド生成(TODO：将来的にはCSVからマップを読み込みたい)
	std::vector<std::shared_ptr<tkl::Mesh>> fields;
	for(int i = 0; i < 4; ++i){
		fields.clear();
		for(int j = 0; j < 4; ++j){
			std::shared_ptr<tkl::Mesh> field = tkl::Mesh::CreatePlane(50);
			field->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test.jpg"));
			field->SetPosition(tkl::Vector3(-75 + 50 * j, 0, -75 + 50 * i));
			field->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90.0f)));

			fields.emplace_back(field);
		}
		mFields.emplace_back(fields);
	}
	
	// 3Dカメラ生成
	tkl::System::GetInstance()->GetWindowSize(&mScreenW, &mScreenH);
	mCamera = std::make_shared<tkl::PostureControlCamera>(mScreenW, mScreenH);
	mCamera->SetPosition(tkl::Vector3(500, 500, 500));

	// 選択カーソル
	mSelectCursor = tkl::Mesh::CreatePlane(50);
	mSelectCursor->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test2.bmp"));
	mSelectCursor->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90.0f)));

	// グリッド生成
	mGrid = tkl::Mesh::CreateGround(50, 4);
}

PlayScene::~PlayScene()
{}

std::shared_ptr<BaseScene> PlayScene::Update(float deltaTime)
{
	std::shared_ptr<BaseScene> nextScene = shared_from_this();
	
	mCamera->Update();

	// マウス座標を元にレイを作成
	int mousePosX = 0, mousePosY = 0;
	tkl::Input::GetMousePoint(&mousePosX, &mousePosY);
	tkl::Vector3 ray = tkl::Vector3::CreateScreenRay(mousePosX, mousePosY, mScreenW, mScreenH, mCamera->GetView(), mCamera->GetProjection());

	// レイと平面の当たり判定
	tkl::Vector3 hit;
	if (tkl::IsIntersectLinePlane(mCamera->GetPosition(), mCamera->GetPosition() + (ray * 10000.0f),
		{ 1, 0, 1 }, { 0, 1, 0 }, &hit))
	{
		tkl::Font::DrawStringEx(0, 0, "PosX : %f, PosY : %f, PosZ : %f", hit.mX, hit.mY, hit.mZ);

		// フィールドを選択しているかを確認
		for(int h = 0; h < mFields.size(); ++h){
			for(int w = 0; w < mFields[h].size(); ++w){
				tkl::Vector3 pos = mFields[h][w]->GetPosition();

				// TODO：Meshからサイズを取得したい
				float left	 = pos.mX - (50 >> 1);
				float right	 = pos.mX + (50 >> 1);
				float top	 = pos.mZ + (50 >> 1);
				float bottom = pos.mZ - (50 >> 1);

				if((left < hit.mX && right > hit.mX) && (bottom < hit.mZ && top > hit.mZ)){
					tkl::Font::DrawStringEx(0, 30, "入りました");
					// マップ選択カーソル位置と描画
					mSelectCursor->SetPosition(pos);
					mSelectCursor->Draw(mCamera);
					
					if(tkl::Input::IsMouseDownTrigger(eMouse::MOUSE_LEFT)){
						// 選択した場所に障害物を生成
						std::shared_ptr<tkl::Mesh> obstacle = tkl::Mesh::CreateBox(50);
						obstacle->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test.jpg"));
						obstacle->SetPosition(tkl::Vector3(pos.mX, pos.mY + (50 >> 1), pos.mZ));
						mObstacleList.emplace_back(obstacle);
					}
				}
			}
		}
	}

	for(int i = 0; i < mFields.size(); ++i){
		for(int j = 0; j < mFields[i].size(); ++j){
			mFields[i][j]->Draw(mCamera);
		}
	}

	for(int i = 0; i < mObstacleList.size(); ++i){
		mObstacleList[i]->Draw(mCamera);
	}

	mGrid->Draw(mCamera);

	return nextScene;
}