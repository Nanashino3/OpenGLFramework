//****************************************************************************
// ファイル名：Bullet(弾クラス)
// 作　成　日：2022/12/6
#include "Bullet.h"

#include "AdvanceUnit.h"
#include "GameParameter.h"
#include "ObjectManager.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Intersect.h"
#include "../../01_Engine/Graphics/Geometry/Mesh.h"

// ファイルパス
static constexpr const char* TEXTURE_FILE = "Resource/texture/panel_concrete.bmp";

// 定数
static constexpr int BULLET_SIZE = 2;
static constexpr int DIVISION_W = 24;
static constexpr int DIVISION_H = 16;
static constexpr int DAMAGE = 5;
static constexpr float OBJECT_HEIGHT = 9.5f;
static constexpr float DESTROY_POS = 70.0f;
static constexpr float MOVE_SPEED = 100.0f;
static constexpr float RECT_SIZE = 8.5f;

Bullet::Bullet(std::shared_ptr<Parameter> param)
: mRadian(0)
, mMesh(nullptr)
, mParam(nullptr)
{
	mParam = std::dynamic_pointer_cast<GameParameter>(param);
}

Bullet::~Bullet()
{}

//****************************************************************************
// 関数名：Initialize
// 概　要：事前準備
// 引　数：なし
// 戻り値：なし
// 詳　細：弾クラスの初期化処理
//****************************************************************************
void Bullet::Initialize(const tkl::Vector3& srcPos, const tkl::Vector3& target)
{
	tkl::Vector3 diff = target - srcPos;
	mRadian = atan2f(diff.mZ, diff.mX);
	mLauncherPos = srcPos;

	mMesh = tkl::Mesh::CreateSphere(BULLET_SIZE, DIVISION_W, DIVISION_H);
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(TEXTURE_FILE));
	mMesh->SetPosition(tkl::Vector3(srcPos.mX, OBJECT_HEIGHT, srcPos.mZ));
}

//****************************************************************************
// 関数名：Collision
// 概　要：衝突処理
// 引　数：なし
// 戻り値：なし
// 詳　細：弾クラスの衝突処理
//****************************************************************************
void Bullet::Collision()
{
	tkl::Vector3 pos = mMesh->GetPosition();

	// 進軍ユニットリストを取得
	const std::list<std::shared_ptr<GameObject>>* list = ObjectManager::GetInstance()->GetList<AdvanceUnit>();
	for(auto it = list->begin(); it != list->end(); ++it){
		std::shared_ptr<AdvanceUnit> unit = std::static_pointer_cast<AdvanceUnit>(*it);		
		tkl::Vector3 unitPos = unit->GetPosition();

		// 進軍ユニットと衝突していたら弾削除
		// TODO：進軍ユニットのサイズを取得できるようにする
		if(tkl::IsIntersectAABB(pos, BULLET_SIZE, unitPos, RECT_SIZE)){
			mIsAlive = false;
			// TODO：与えるダメージは可変にしたい
			unit->ReceiveDamage(DAMAGE);
			break; 
		}
	}
}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：なし
// 戻り値：なし
// 詳　細：弾クラスの更新処理
//****************************************************************************
void Bullet::Update()
{
	tkl::Vector3 pos = mMesh->GetPosition();

	// 進む方向計算
	pos.mX += cosf(mRadian) * MOVE_SPEED * mParam->GetDeltaTime();
	pos.mZ += sinf(mRadian) * MOVE_SPEED * mParam->GetDeltaTime();

	// 一定距離まで行ったら弾削除
	float dist = tkl::Vector3::Distance(mLauncherPos, pos);
	if(dist > DESTROY_POS){ mIsAlive = false; }

	mMesh->SetPosition(pos);
}

//****************************************************************************
// 関数名：Draw
// 概　要：描画
// 引　数：なし
// 戻り値：なし
// 詳　細：弾クラスの描画処理
//****************************************************************************
void Bullet::Draw()
{
	if(mIsAlive){ mMesh->Draw(mParam->GetCamera()); }
}