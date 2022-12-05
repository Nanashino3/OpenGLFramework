#include "DefenseUnit.h"

#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/ResourceManager.h"

DefenseUnit::DefenseUnit(const tkl::Vector3& pos)
{
	mMesh = tkl::Mesh::CreateSphere(25, 24, 16);
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/panel_water.bmp"));
	mMesh->SetPosition(tkl::Vector3(pos.mX, 12.5f, pos.mZ));
}

DefenseUnit::~DefenseUnit()
{}

void DefenseUnit::Update(float deltaTime, std::shared_ptr<tkl::Camera> camera)
{
	mMesh->Draw(camera);
}