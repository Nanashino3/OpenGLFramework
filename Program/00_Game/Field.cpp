//****************************************************************************
// ファイル名：Field(フィールドクラス)
// 作　成　日：2022/12/11
#include "Field.h"

#include "../00_Game/GameObject/GameParameter.h"
#include "../00_Game/NotifyService/Notifier.h"

#include "../01_Engine/Camera/Camera.h"
#include "../01_Engine/Mesh.h"
#include "../01_Engine/System.h"
#include "../01_Engine/Intersect.h"
#include "../01_Engine/ResourceManager.h"

#include "../02_Library/Input.h"
#include "../02_Library/Utility.h"
#include "../02_Library/Math.h"

const int MAP_SIZE = 50;

Field::Field(std::shared_ptr<GameParameter> param)
: mScreenW(0), mScreenH(0)
, mStartPosX(0), mStartPosZ(0)
, mCursor(nullptr)
, mGrid(nullptr)
{
	// グリッド生成
	mGrid = tkl::Mesh::CreateGround(50, 5);

	// ウィンドウサイズを取得
	tkl::System::GetInstance()->GetWindowSize(&mScreenW, &mScreenH);

	// カーソル生成
	mCursor = tkl::Mesh::CreatePlane(50);
	mCursor->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test2.bmp"));
	mCursor->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));

	// フィールド情報読み込み
	auto readField = tkl::LoadCsv("Resource/test.csv");
	for(int r = 0; r < readField.size(); ++r){
		std::vector<tkl::CELL> fields;
		for(int c = 0; c < readField[r].size(); ++c){
			fields.emplace_back(tkl::CELL(r, c, static_cast<tkl::STATUS>(std::stoi(readField[r][c]))));
		}
		mFields.emplace_back(fields);
	}

	int mapRow = readField.size();
	int mapColumn = readField[0].size();

	// スタート位置を計算
	mStartPosX = -MAP_SIZE * mapRow * 0.5f + (MAP_SIZE >> 1);
	mStartPosZ = -MAP_SIZE * mapColumn * 0.5f + (MAP_SIZE >> 1);

	param->SetMapSize(MAP_SIZE);
	param->SetMapRow(mapRow);
	param->SetMapColumn(mapColumn);
	param->SetFields(mFields);
}

Field::~Field()
{}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：arg1 ゲームパラメータ
// 戻り値：なし
// 詳　細：フィールドクラスの更新処理
//****************************************************************************
void Field::Update(std::shared_ptr<GameParameter>& param)
{
	std::shared_ptr<tkl::Camera> camera = param->GetCamera();

	// マウス座標を元にレイを飛ばす
	int mousePosX = 0, mousePosY = 0;
	tkl::Input::GetMousePoint(&mousePosX, &mousePosY);
	tkl::Vector3 ray = tkl::Vector3::CreateScreenRay(mousePosX, mousePosY,
		mScreenW, mScreenH, camera->GetView(), camera->GetProjection());

	// レイと平面の当たり判定
	tkl::Vector3 hit;
	if (tkl::IsIntersectLinePlane(camera->GetPosition(), camera->GetPosition() + ray * 1000.0f,
		{ 1, 0, 0 }, tkl::Vector3::UNITY, &hit))
	{
		PriSelectField(param, hit);
	}
}

//****************************************************************************
// 関数名：Draw
// 概　要：描画
// 引　数：arg1 ゲームパラメータ
// 戻り値：なし
// 詳　細：フィールドクラスの描画処理
//****************************************************************************
void Field::Draw(std::shared_ptr<GameParameter>& param)
{
	// グリッド生成
	mGrid->Draw(param->GetCamera());
}

//****************************************************************************
// 関数名：PriSelectField(private)
// 概　要：フィールド選択
// 引　数：arg1 ゲームパラメータ
//       ：arg2 レイと平面の当たった位置
// 戻り値：なし
// 詳　細：フィールドのどの位置に防衛ユニットを置くか選択する
//****************************************************************************
void Field::PriSelectField(std::shared_ptr<GameParameter> param, const tkl::Vector3& pos)
{
	for (int r = 0; r < mFields.size(); ++r) {
		for (int c = 0; c < mFields[r].size(); ++c) {
			float posX = mStartPosX + MAP_SIZE * c;
			float posZ = mStartPosZ + MAP_SIZE * r;
			if (!tkl::IsIntersectPointRect(pos.mX, pos.mZ, posX, posZ, MAP_SIZE)) { continue; }

			// 編集可状態のみ処理する
			if(mFields[r][c].status == tkl::STATUS::EDITABLE){

				mCursor->SetPosition(tkl::Vector3(posX, 0, posZ));
				mCursor->Draw(param->GetCamera());

				if(!tkl::Input::IsMouseDownTrigger(tkl::eMouse::MOUSE_LEFT)) { continue; }

				// フィールド状態変化通知
				param->SetClickPos(tkl::Vector3(posX, 0, posZ));
				Notifier::GetInstance()->FieldStateChange(r, c, param);
			}
		}
	}
}