//****************************************************************************
// ファイル名：Cell(マスクラス)
// 作　成　日：2022/12/17
#include "Cell.h"

#include "../GameObject/GameParameter.h"
#include "../NotifyService/Notifier.h"

#include "../../01_Engine/Intersect.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Graphics/Geometry/Mesh.h"
#include "../../01_Engine/Graphics/Geometry/Model.h"

#include "../../02_Library/Math.h"
#include "../../02_Library/Input.h"

// ファイルパス
static constexpr const char* TEXTURE_FIELD  = "Resource/texture/panel_soil.bmp";
static constexpr const char* TEXTURE_START  = "Resource/texture/red.png";
static constexpr const char* TEXTURE_GAOL   = "Resource/texture/blue.png";
static constexpr const char* TEXTURE_CURSOR = "Resource/texture/frame_green.png";
static constexpr const char* MODEL_FILE = "Resource/model/crate/SciFi_Crate.obj";

// 定数
static constexpr float PLANE_SIZE = 50.0f;
static constexpr float OBSTACLE_SIZE = 10.0f;
static constexpr float BLOCK_SIZE = 15.0f;
static constexpr float BASE_MESH_HEIGHT = 0.1f;
static constexpr float CURSOR_SIZE = 50.0f;
static constexpr float CURSOR_HEIGHT = 0.5f;

Cell::Cell(std::shared_ptr<Parameter> param)
: mIsSelecting(false)
, mModel(nullptr)
, mCursor(nullptr)
, mParam(nullptr)
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
void Cell::Initialize(const tkl::CELL& cell)
{
	// 座標計算
	int mapSize = mParam->GetMapSize();
	int mapRow = mParam->GetMapRow();
	int mapColumn = mParam->GetMapColumn();

	float initPosX = -mapSize * mapColumn * 0.5f + (mapSize >> 1);
	float initPosZ = -mapSize * mapRow * 0.5f + (mapSize >> 1);

	float posX = initPosX + mapSize * cell.column;
	float posZ = initPosZ + mapSize * cell.row;

	//*****************************************************************************************
	// マスに何を生成するかを状態で決める
	
	// フロア生成
	std::shared_ptr<tkl::Mesh> mesh = tkl::Mesh::CreatePlane(PLANE_SIZE);
	mesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_FIELD));
	mesh->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));
	mesh->SetPosition(tkl::Vector3(posX, 0.0f, posZ));
	mMeshList.emplace_back(mesh);

	// 敵出現位置とゴール位置の生成
	if(cell.status == tkl::eStatus::START || cell.status == tkl::eStatus::GOAL){
		mesh = tkl::Mesh::CreatePlane(PLANE_SIZE);
		mesh->SetIsBlend(true);
		mesh->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));
		mesh->SetPosition(tkl::Vector3(posX, BASE_MESH_HEIGHT, posZ));

		// テクスチャの設定
		std::string file = "";
		if(cell.status == tkl::eStatus::START){
			file = TEXTURE_START;
		}else if(cell.status == tkl::eStatus::GOAL){
			file = TEXTURE_GAOL;
		}
		mesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(file.c_str()));
		mMeshList.emplace_back(mesh);
	}

	// 障害物生成
	if(cell.status == tkl::eStatus::OBSTACLE){
		mModel = tkl::Model::CreateModelFromObjFile(MODEL_FILE);
		mModel->SetPosition(tkl::Vector3(posX, BLOCK_SIZE, posZ));
		mModel->SetScale(tkl::Vector3(OBSTACLE_SIZE, OBSTACLE_SIZE, OBSTACLE_SIZE));
	}
	//*****************************************************************************************

	// カーソル生成
	mCursor = tkl::Mesh::CreatePlane(CURSOR_SIZE);
	mCursor->SetIsBlend(true);
	mCursor->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_CURSOR));
	mCursor->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));

	mCell = cell;
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
	mIsSelecting = false;
	tkl::Vector3 pos = mMeshList.at(0)->GetPosition();
	if(tkl::IsIntersectPointRect(mousePos.mX, mousePos.mZ, pos.mX, pos.mZ, mParam->GetMapSize())){
		if(mCell.status != tkl::eStatus::EDITABLE){ return; }

		mIsSelecting = true;
		mCursor->SetPosition(tkl::Vector3(pos.mX, CURSOR_HEIGHT, pos.mZ));

		if(tkl::Input::IsMouseDownTrigger(tkl::eMouse::MOUSE_LEFT)){
			// フィールド状態変化通知
			mParam->SetClickPos(tkl::Vector3(pos.mX, 0.0f, pos.mZ));
			Notifier::GetInstance()->FieldStateChange(mCell.row, mCell.column, mParam);
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
	if(mModel != nullptr){ mModel->Draw(mParam->GetCamera()); }
	if(mIsSelecting){ mCursor->Draw(mParam->GetCamera()); }
}