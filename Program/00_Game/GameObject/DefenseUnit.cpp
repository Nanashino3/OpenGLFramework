//****************************************************************************
// ファイル名：DefenseUnit(防衛ユニットクラス)
// 作　成　日：2022/12/5
#include "DefenseUnit.h"

#include "Bullet.h"
#include "AdvanceUnit.h"
#include "GameParameter.h"
#include "ObjectManager.h"

#include "../../01_Engine/Sound/Sound.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Graphics/Geometry/Model.h"

#include "../../02_Library/Math.h"

// ファイルパス
static constexpr const char* MODEL_FILE = "Resource/Model/Turret/1/Turret.obj";
static constexpr const char* SOUND_FILE = "Resource/sound/shot.wav";

// 定数
static constexpr int CONSUME_COST = 75;
static constexpr float MODEL_SCALE = 15;
static constexpr float DIST_MAX = 70.0f;
static constexpr float CREATE_INTERVAL = 0.8f;

DefenseUnit::DefenseUnit(std::shared_ptr<Parameter> param)
: mElapsedTime(0.0f)
, mModel(nullptr)
, mSound(nullptr)
, mParam(nullptr)
{
	mParam = std::dynamic_pointer_cast<GameParameter>(param);	
}

DefenseUnit::~DefenseUnit()
{}

//****************************************************************************
// 関数名：Initialize
// 概　要：更新処理
// 引　数：なし
// 戻り値：なし
// 詳　細：防衛ユニットクラスの初期化処理
//****************************************************************************
void DefenseUnit::Initialize()
{
	mSound = tkl::Sound::CreateSound(SOUND_FILE);

	tkl::Vector3 clickPos = mParam->GetClickPos();

	mModel = tkl::Model::CreateModelFromObjFile(MODEL_FILE);
	mModel->SetPosition(tkl::Vector3(clickPos));
	mModel->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITY, tkl::ToRadian(90)));
	mModel->SetScale(tkl::Vector3(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));

	mParam->SetTotalCost(mParam->GetTotalCost() - CONSUME_COST);
}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：なし
// 戻り値：なし
// 詳　細：防衛ユニットクラスの更新処理
//****************************************************************************
void DefenseUnit::Update()
{
	tkl::Quaternion rot = mModel->GetRotation();
	tkl::Vector3 modelPos = mModel->GetPosition();

	// 1番近い進軍ユニットを探す
	tkl::Vector3 nearPos;
	const std::list<std::shared_ptr<GameObject>>* list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
	for(auto iter = list->begin(); iter != list->end(); ++iter){
		std::shared_ptr<AdvanceUnit> unit = std::dynamic_pointer_cast<AdvanceUnit>(*iter);
		tkl::Vector3 unitPos = unit->GetPosition();

		float dist = tkl::Vector3::Distance(unitPos, modelPos);
		if(dist <= DIST_MAX){
			// 進軍ユニットの方向に向く
			nearPos = tkl::Vector3(unitPos.mX, 0.0f, unitPos.mZ);
			tkl::Vector3 dir = nearPos - modelPos;
			float theta = tkl::ToDegree(std::atan2f(dir.mX, dir.mZ));
			rot = tkl::Quaternion::RotationAxis(tkl::Vector3::UNITY, tkl::ToRadian(-theta));
			break;
		}
	}

	// 弾を撃つ
	Shoot(nearPos);

	mModel->SetRotation(rot);
}

//****************************************************************************
// 関数名：Draw
// 概　要：描画
// 引　数：なし
// 戻り値：なし
// 詳　細：防衛ユニットクラスの描画処理
//****************************************************************************
void DefenseUnit::Draw()
{
	mModel->Draw(mParam->GetCamera());
}

//****************************************************************************
// 関数名：Shoot
// 概　要：弾を撃つ
// 引　数：arg1 目標位置
// 戻り値：なし
// 詳　細：弾を撃つ処理(弾を撃つかどうかも判断する)
//****************************************************************************
void DefenseUnit::Shoot(const tkl::Vector3& targetPos)
{
	// 弾が消えていれば新しく生成する
	if(!mBullet.expired() || (tkl::Vector3::Magnitude(targetPos) == 0)){ return; }

	// 弾が消滅してから秒後に発射する
	// TODO：インターバルは可変にしたい
	mElapsedTime += mParam->GetDeltaTime();
	if(mElapsedTime > CREATE_INTERVAL){
		mElapsedTime = 0.0f;

		// 弾関連処理
		mBullet = ObjectManager::GetInstance()->Create<Bullet>(mParam);
		std::shared_ptr<Bullet> bullet = mBullet.lock();
		bullet->Initialize(mModel->GetPosition(), targetPos);

		mSound->Play();
	}
}