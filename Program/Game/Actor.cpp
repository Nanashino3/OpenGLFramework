#include "Actor.h"

Actor::Actor()
{}

Actor::~Actor()
{}

void Actor::Update()
{
	for(auto component : mComponents){
		component->Update();
	}

	mWorldTransform = Matrix::CreateTranslation(mPosition);
	mWorldTransform *= Matrix::CreateRotationFromQuaternion(mRotation);
	mWorldTransform *= Matrix::CreateScale(mScale);
}