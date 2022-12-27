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

static constexpr const char* MODEL_FILE = "Resource/Model/Turret/1/Turret.obj";
static constexpr const char* SOUND_FILE = "Resource/sound/shot.wav";
static constexpr float CREATE_SIZE = 25;
static constexpr float DIST_MAX = 60.0f;
static constexpr int CONSUME_COST = 75;

DefenseUnit::DefenseUnit(std::shared_ptr<Parameter> param)
: mElapsed(0)
, mParam(nullptr)
, mModel(nullptr)
, mSound(nullptr)
{
	mParam = std::dynamic_pointer_cast<GameParameter>(param);	
	mSound = tkl::Sound::CreateSound(SOUND_FILE);
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
	tkl::Vector3 clickPos = mParam->GetClickPos();

	mModel = tkl::Model::CreateModelFromObjFile(MODEL_FILE);
	mModel->SetPosition(clickPos);
	mModel->SetScale(tkl::Vector3(15, 15, 15));

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
	if(!mBullet.expired()){ return; }

	// 弾が消滅してから秒後に発射する
	// TODO：インターバルは可変にしたい
	mElapsed += mParam->GetDeltaTime();
	if(mElapsed < 0.8f){ return; }
	mElapsed = 0;

	// 生存していない場合は弾生成
	auto list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
	tkl::Vector3 nearPos;
	for (auto it = list->begin(); it != list->end(); ++it) {
		std::shared_ptr<AdvanceUnit> unit = std::static_pointer_cast<AdvanceUnit>(*it);
		tkl::Vector3 pos = unit->GetUnitPosition();
		float dist = tkl::Vector3::Distance(pos, mModel->GetPosition());

		if(dist <= DIST_MAX){
			nearPos = pos;
			break;
		}
	}
	if(tkl::Vector3::Magnitude(nearPos) == 0){ return; }

	// 弾関連処理
	mBullet = ObjectManager::GetInstance()->Create<Bullet>(mParam);
	std::shared_ptr<Bullet> bullet = mBullet.lock();
	bullet->SetLauncherPos(mModel->GetPosition());
	bullet->SetTargetPos(nearPos);
	bullet->Initialize();

	mSound->Play();
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