//****************************************************************************
// ファイル名：Cell(マスクラス)
// 作　成　日：2022/12/17
#include "Cell.h"

#include "../GameObject/GameParameter.h"
#include "../NotifyService/Notifier.h"

#include "../../01_Engine/Intersect.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Graphics/Geometry/Mesh.h"

#include "../../02_Library/Math.h"
#include "../../02_Library/Input.h"

static constexpr int PLANE_SIZE = 50;
static constexpr int BLOCK_SIZE = 30;
static constexpr const char* TEXTURE_FIELD = "Resource/panel_soil.bmp";
static constexpr const char* TEXTURE_BLOCK = "Resource/panel_grass.bmp";
static constexpr const char* TEXTURE_CURSOR = "Resource/debug/test2.bmp";

Cell::Cell(std::shared_ptr<Parameter> param)
{
	mParam = std::dynamic_pointer_cast<GameParameter>(param);
}

Cell::~Cell()
{}

//****************************************************************************
// 関数名：Initialize
// 概　要：初期化処理
// 引　数：なし
// 戻り値：なし
// 詳　細：マスクラスの初期化処理
//****************************************************************************
void Cell::Initialize()
{
	// 座標計算
	int mapSize = mParam->GetMapSize();
	int mapRow = mParam->GetMapRow();
	int mapColumn = mParam->GetMapColumn();
	
	float initPosX = -mapSize * mapRow * 0.5f + (mapSize >> 1);
	float initPosZ = -mapSize * mapColumn * 0.5f + (mapSize >> 1);

	float posX = initPosX + mapSize * mCellInfo.column;
	float posZ = initPosZ + mapSize * mCellInfo.row;

	// TODO：マスに何を生成するかを状態で決める
	std::shared_ptr<tkl::Mesh> mesh = tkl::Mesh::CreatePlane(PLANE_SIZE);
	mesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_FIELD));
	mesh->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));
	mesh->SetPosition(tkl::Vector3(posX, 0, posZ));
	mMeshList.emplace_back(mesh);

	if(mCellInfo.status == tkl::STATUS::OBSTACLE){
		mesh = tkl::Mesh::CreateBox(BLOCK_SIZE);
		mesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_BLOCK));
		mesh->SetPosition(tkl::Vector3(posX, BLOCK_SIZE >> 1, posZ));
		mMeshList.emplace_back(mesh);
	}

	// カーソル生成
	mCursor = tkl::Mesh::CreatePlane(50);
	mCursor->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_CURSOR));
	mCursor->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));
}

//****************************************************************************
// 関数名：Collision
// 概　要：衝突処理
// 引　数：なし
// 戻り値：なし
// 詳　細：マスクラスの衝突処理
//****************************************************************************
void Cell::Collision()
{
	tkl::Vector3 mousePos = mParam->GetMousePos();

	// 自分が選択されているか確認
	tkl::Vector3 pos = mMeshList.at(0)->GetPosition();
	if(tkl::IsIntersectPointRect(mousePos.mX, mousePos.mZ, pos.mX, pos.mZ, mParam->GetMapSize())){
		if(mCellInfo.status != tkl::STATUS::EDITABLE){ return; }

		mCursor->SetPosition(tkl::Vector3(pos.mX, 0.5f, pos.mZ));
		mCursor->Draw(mParam->GetCamera());

		if(tkl::Input::IsMouseDownTrigger(tkl::eMouse::MOUSE_LEFT)){

			// フィールド状態変化通知
			mParam->SetClickPos(tkl::Vector3(pos.mX, 0, pos.mZ));
			Notifier::GetInstance()->FieldStateChange(mCellInfo.row, mCellInfo.column, mParam);
		}
	}
}

//****************************************************************************
// 関数名：Draw
// 概　要：描画処理
// 引　数：なし
// 戻り値：なし
// 詳　細：マスクラスの描画処理
//****************************************************************************
void Cell::Draw()
{
	for(auto mesh : mMeshList){
		mesh->Draw(mParam->GetCamera());
	}
}