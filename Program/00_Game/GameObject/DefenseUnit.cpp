#include "DefenseUnit.h"

#include "Bullet.h"
#include "AdvanceUnit.h"
#include "GameParameter.h"
#include "ObjectManager.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/ResourceManager.h"

DefenseUnit::DefenseUnit(std::shared_ptr<GameParameter> param)
: mMesh(nullptr)
{
	mMesh = tkl::Mesh::CreateSphere(25, 24, 16);
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/panel_water.bmp"));

	tkl::Vector3 clickPos = param->GetClickPos();
	mMesh->SetPosition(tkl::Vector3(clickPos.mX, 12.5f, clickPos.mZ));
}

DefenseUnit::~DefenseUnit()
{}

void DefenseUnit::Update(std::shared_ptr<GameParameter> param)
{
	// Ž©g‚ð•`‰æ
	mMesh->Draw(param->GetCamera());
	if(!mBullet.expired()){ return; }
	
	// ¶‘¶‚µ‚Ä‚¢‚È‚¢ê‡‚Í’e¶¬
	auto list = ObjectManager::GetInstance()->GetObjectList<AdvanceUnit>();
	if(list->size() != 0){
		tkl::Vector3 nearPos;
		for(auto it = list->begin(); it != list->end(); ++it){
			std::shared_ptr<AdvanceUnit> unit = std::static_pointer_cast<AdvanceUnit>(*it);
			tkl::Vector3 pos = unit->GetUnitPosition();
			float distance = tkl::Vector3::Distance(pos, mMesh->GetPosition());
			if(distance <= 55.0f){ nearPos = pos; break; }
		}
		if(tkl::Vector3::Magnitude(nearPos) == 0){ return; }

		param->SetTargetPos(nearPos);
		param->SetLauncherPos(mMesh->GetPosition());
		mBullet = ObjectManager::GetInstance()->Create<Bullet>(param);
	}
}