//****************************************************************************
// ファイル名：AdvanceUnit(進軍ユニットクラス)
// 作　成　日：2022/12/4
#include "AdvanceUnit.h"

#include <iostream>
#include "GameParameter.h"

#include "../../01_Engine/Sound/Sound.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Graphics/Geometry/Model.h"

#include "../../02_Library/Math.h"
#include "../../02_Library/Utility.h"

static constexpr const char* CSV_PATH = "Resource/AdvanceInfo.csv";
static constexpr const char* OBJECT_FILE = "Resource/model/UFO/TriangleUFO.obj";
static constexpr const char* DISAPPER_SOUND = "Resource/sound/disapper.wav";

AdvanceUnit::AdvanceUnit(std::shared_ptr<Parameter> param)
: mRouteCount(0)
, mMapInitPosX(0), mMapInitPosZ(0)
, mMoveSpeed(0)
, mHitPoint(0)
, mAddCoin(0)
, mPrevDx(0), mPrevDz(0)
, mAngle(0)
, mModel(nullptr)
{
	mUnitInfo = tkl::LoadCsv(CSV_PATH);
	mParam = std::dynamic_pointer_cast<GameParameter>(param);
	mSound = tkl::Sound::CreateSound(DISAPPER_SOUND);

	mIsRetNewRoute = false;
	mPrevRouteCount = 0;
}

AdvanceUnit::~AdvanceUnit()
{}

//****************************************************************************
// 関数名：Initialize
// 概　要：初期化処理
// 引　数：なし
// 戻り値：なし
// 詳　細：進軍ユニットクラスの描画処理
//****************************************************************************
void AdvanceUnit::Initialize()
{
	int mapSize = mParam->GetMapSize();
	int mapRow = mParam->GetMapRow();
	int mapColumn = mParam->GetMapColumn();
	std::vector<std::vector<tkl::CELL>> field = mParam->GetFields();

	// 経路検索(初期)
	tkl::Algorithm::RouteSearch(mapRow, mapColumn, field, mRoute);
	
	// 初期移動方向計算
	mRouteCount = mRoute.size() - 1;
	mPrevDx = mRoute[mRouteCount - 1].column - mRoute[mRouteCount].column;
	mPrevDz = mRoute[mRouteCount - 1].row - mRoute[mRouteCount].row;

	if(mPrevDx != 0){ mAngle = (mPrevDx > 0) ?  90 : 270; }
	if(mPrevDz != 0){ mAngle = (mPrevDz > 0) ? 180 : 360; }
	tkl::Quaternion rot;
	rot *= tkl::Quaternion::RotationAxis(tkl::Vector3::UNITY, tkl::ToRadian(mAngle));

	// 初期座標計算
	mMapInitPosX = -mapSize * mapRow * 0.5f + (mapSize >> 1);
	mMapInitPosZ = -mapSize * mapColumn * 0.5f + (mapSize >> 1);

	float posX = mMapInitPosX + mParam->GetMapSize() * mRoute[mRouteCount].column;
	float posZ = mMapInitPosZ + mParam->GetMapSize() * mRoute[mRouteCount].row;

	// モデルの生成と設定
	mModel = tkl::Model::CreateModelFromObjFile(OBJECT_FILE);
	mModel->SetPosition(tkl::Vector3(posX, 10, posZ));
	mModel->SetScale(tkl::Vector3(3.5f, 3.5f, 3.5f));
	mModel->SetRotation(rot);

	// 進軍ユニットのレベル設定
	int level = mParam->GetAdvenceLevel();
	if(stoi(mUnitInfo[level][0]) <= mParam->GetTotalDefeat() && (level + 1) < mUnitInfo.size()){
		mParam->SetAdvanceLevel(level + 1);
		mParam->SetTotalDefeat(0);
	}
	mHitPoint = stoi(mUnitInfo[level][1]);
	mMoveSpeed = stoi(mUnitInfo[level][2]);
	mAddCoin = stoi(mUnitInfo[level][3]);
}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：なし
// 戻り値：なし
// 詳　細：進軍ユニットクラスの更新処理
//****************************************************************************
void AdvanceUnit::Update()
{
	if(mRouteCount == 0 && mRoute[mRouteCount].status == tkl::STATUS::GOAL){
		mIsAlive = false;
		mParam->SetIsArrival(true);
		return;
	}
	tkl::Vector3 pos = mModel->GetPosition();
	tkl::Quaternion rot = mModel->GetRotation();

	//******************************************************************
	// 移動量計算
	int column = (mIsRetNewRoute) ? mPrevRoute[mPrevRouteCount - 1].column : mRoute[mRouteCount].column;
	int row = (mIsRetNewRoute) ? mPrevRoute[mPrevRouteCount - 1].row : mRoute[mRouteCount].row;

	int dx = mRoute[mRouteCount - 1].column - column;
	int dz = mRoute[mRouteCount - 1].row - row;
	//******************************************************************

	//******************************************************************
	// 方向転換計算
	float angles[] = { 90, 180, 270, 360 };
	enum { RIGHT, BOTTOM, LEFT, TOP };

	float diffAngle = 0;
	if(dx != 0 && mPrevDx != dx){
		int dir = (dx > 0) ? RIGHT : LEFT;
		diffAngle = angles[dir] - mAngle;
	}

	if(dz != 0 && mPrevDz != dz){
		int dir = (dz > 0) ? BOTTOM : TOP;
		diffAngle = angles[dir] - mAngle;
	}
	rot *= tkl::Quaternion::RotationAxis(tkl::Vector3::UNITY, tkl::ToRadian(diffAngle));
	mAngle += diffAngle;
	//******************************************************************

	//******************************************************************
	// 探索した経路を進む処理
	int mapSize = mParam->GetMapSize();
	float targetPosX = mMapInitPosX + mapSize * mRoute[mRouteCount - 1].column;
	float targetPosZ = mMapInitPosZ + mapSize * mRoute[mRouteCount - 1].row;

	pos.mX += mMoveSpeed * dx * mParam->GetDeltaTime();
	pos.mZ += mMoveSpeed * dz * mParam->GetDeltaTime();

	bool retX = (dx > 0) ? pos.mX > targetPosX : pos.mX < targetPosX;
	if(retX){ pos.mX = targetPosX; }

	bool retZ = (dz > 0) ? pos.mZ > targetPosZ : pos.mZ < targetPosZ;
	if(retZ){ pos.mZ = targetPosZ; }

	bool isIncrement = (dx == 0 || dz == 0) ? retX || retZ : retX && retZ;
	if(isIncrement && mRouteCount > 0){
		mRouteCount--;
		if(mIsRetNewRoute){ mIsRetNewRoute = false;}
	}
	//******************************************************************

	mPrevDx = dx, mPrevDz = dz;

	mModel->SetPosition(pos);
	mModel->SetRotation(rot);
}

//****************************************************************************
// 関数名：Draw
// 概　要：描画
// 引　数：なし
// 戻り値：なし
// 詳　細：進軍ユニットクラスの描画処理
//****************************************************************************
void AdvanceUnit::Draw()
{
//	PrintRoute();
	mModel->Draw(mParam->GetCamera());
}

//****************************************************************************
// 関数名：IsAlive
// 概　要：生存しているか
// 引　数：なし
// 戻り値：なし
// 詳　細：生存しているかの確認
//****************************************************************************
bool AdvanceUnit::IsAlive()
{
	if(!mIsAlive && mHitPoint <= 0){
		mParam->SetTotalCost(mParam->GetTotalCost() + mAddCoin);
		mParam->SetTotalDefeat(mParam->GetTotalDefeat() + 1);
		mSound->Play();
	}
	return mIsAlive;
}

//****************************************************************************
// 関数名：ReceiveDamage
// 概　要：ダメージを受ける
// 引　数：arg1 受けるダメージ数
// 戻り値：なし
// 詳　細：ダメージの処理をする(TODO：もっといい方法があれば作り変える)
//****************************************************************************
void AdvanceUnit::ReceiveDamage(int damage)
{
	mHitPoint -= damage;
	if(mHitPoint <= 0){ mIsAlive = false; }
}

//****************************************************************************
// 関数名：GetPosition
// 概　要：座標取得
// 引　数：なし
// 戻り値：モデルの座標
// 詳　細：進軍ユニット自身の位置を返す
//****************************************************************************
const tkl::Vector3& AdvanceUnit::GetPosition() const
{
	return mModel->GetPosition();
}

//****************************************************************************
// 関数名：SetNewRoute(private)
// 概　要：最新ルート設定
// 引　数：arg1 最新ルート
// 戻り値：なし
// 詳　細：最新のルートを設定する
//****************************************************************************
void AdvanceUnit::SetNewRoute(const std::vector<tkl::CELL>& newRoute)
{
	if(IsPassing()){
//		printf("通り過ぎています\n"); 
		return;
	}
//	printf("通り過ぎていません\n");

	// 進行済ルートカウントの再計算
	int prevSize = mRoute.size(), currentSize = newRoute.size();
	int diffSize = abs(prevSize - currentSize);
	int newRoutCount = mRouteCount + diffSize;

	// 新ルートに戻るか確認
	if((mRoute[mRouteCount - 1].row != newRoute[newRoutCount - 1].row) ||
		(mRoute[mRouteCount - 1].column != newRoute[newRoutCount - 1].column))
	{
//		printf("新ルートに戻ります\n");
		mPrevRoute = mRoute;
		mPrevRouteCount = mRouteCount;
		mIsRetNewRoute = true;
	}

	// ルート更新
	mRouteCount = newRoutCount;
	mRoute = newRoute;
}

//****************************************************************************
// 関数名：IsPassing(private)
// 概　要：通過しているか
// 引　数：なし
// 戻り値：なし
// 詳　細：新ルートを設定する際に指定したセルを通過しているかどうかで
//       ：新ルートに戻るかどうかを判定する
//****************************************************************************
bool AdvanceUnit::IsPassing()
{
	// 押下位置から行列を求める
	tkl::Vector3 clickPos = mParam->GetClickPos();
	int clickColumn = abs((mMapInitPosX - clickPos.mX) / mParam->GetMapSize());
	int clickRow    = abs((mMapInitPosZ - clickPos.mZ) / mParam->GetMapSize());

	int nowColumn = mRoute[mRouteCount].column;
	int nowRow = mRoute[mRouteCount].row;

	// 進軍ユニットの位置と同じ位置に置かれた場合のみ通過判定する
	if(clickColumn == nowColumn && clickRow == nowRow){
		// 移動方向計算
		int dx = mRoute[mRouteCount - 1].column - mRoute[mRouteCount].column;
		int dz = mRoute[mRouteCount - 1].row - mRoute[mRouteCount].row;

		tkl::Vector3 pos = mModel->GetPosition();

		bool retX = false, retZ = false;
		if (dx != 0) { retX = (dx > 0) ? pos.mX > clickPos.mX : pos.mX < clickPos.mX; }
		if (dz != 0) { retZ = (dz > 0) ? pos.mZ > clickPos.mZ : pos.mZ < clickPos.mZ; }

		return (dx == 0 || dz == 0) ? retX || retZ : retX && retZ;
	}

	return false;
}

//****************************************************************************
// 関数名：PrintRoute(private)
// 概　要：ルート表示(デバッグ用)
// 引　数：なし
// 戻り値：なし
// 詳　細：現在進行中のルートを描画する
//****************************************************************************
void AdvanceUnit::PrintRoute()
{
	for (int i = 0; i < mRoute.size(); ++i) {
		std::shared_ptr<tkl::Mesh> mesh = tkl::Mesh::CreatePlane(mParam->GetMapSize());

        float posX = mMapInitPosX + mParam->GetMapSize() * mRoute[i].column;
        float posZ = mMapInitPosZ + mParam->GetMapSize() * mRoute[i].row;
        mesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/debug/route.bmp"));
        mesh->SetPosition(tkl::Vector3(posX, 0.1f, posZ));
        mesh->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));
        mesh->Draw(mParam->GetCamera());
	}
}