#pragma once
#include <vector>
#include "Component/Component.h"
#include "../Library/Vector.h"
#include "../Library/Quaternion.h"
#include "../Library/Matrix.h"

class Component;
class Actor
{
public:
	Actor();
	~Actor();

	void Update();

	void SetPosition(const Vector3& p){ mPosition = p; }
	void SetRotation(const Quaternion& q){ mRotation = q; }
	void SetScale(const Vector3& s){ mScale = s; }

	Matrix GetWorldTransform() const{ return mWorldTransform; }

	void AddComponent(Component* comp){ mComponents.emplace_back(comp); }
private:
	Vector3 mPosition;
	Quaternion mRotation;
	Vector3 mScale;
	Matrix mWorldTransform;

	std::vector<Component*> mComponents;
};