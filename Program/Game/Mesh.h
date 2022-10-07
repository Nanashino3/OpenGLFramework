#pragma once
#include <memory>
#include "../Library/Vector.h"
#include "../Library/Quaternion.h"

class Camera;
class VertexArray;
class Renderer;

class Mesh
{
public:
	Mesh();
	~Mesh();

	void Render(Camera* camera);

	static Mesh* CreateBox(float sizeW, float sizeH, float sizeD);
	static Mesh* CreateSphere(float radius, int divWidth, int divHeight);

	std::unique_ptr<VertexArray> mVertexArray;
	Vector3 mPosition;
	Quaternion mRotation;
	Vector3 mScale;

	Renderer* mRenderer;
};