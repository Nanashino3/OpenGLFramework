#include "Bullet.h"

#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/ResourceManager.h"

Bullet::Bullet(const tkl::Vector3& pos)
{
	mMesh = tkl::Mesh::CreateSphere(5, 24, 16);
	mMesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/panel_concrete.bmp"));
	mMesh->SetPosition(pos);
}

Bullet::~Bullet()
{}

void Bullet::Update(float deltaTime, std::shared_ptr<tkl::Camera> camera)
{
	tkl::Vector3 pos = mMesh->GetPosition();

	pos.mX += 10.0f * deltaTime;

	mMesh->SetPosition(pos);
	mMesh->Draw(camera);
}