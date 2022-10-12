#pragma once
#include <memory>
#include "VertexArray.h"
#include "../Library/Vector.h"
#include "../Library/Matrix.h"
#include "../Library/Quaternion.h"

class Camera;
class Renderer;
class Mesh
{
public:
	std::unique_ptr<VertexArray> mVertexArray;

	Mesh(unsigned int type);
	~Mesh();

	void Draw(Camera* camera);

	void SetPosition(const Vector3& pos){ mPosition = pos; }
	Vector3 GetPosition() const{ return mPosition; }

	void SetRotation(const Quaternion& rot){ mRotation = rot; }
	Quaternion GetRotation() const{ return mRotation; }

	void SetScale(const Vector3& scale){ mScale = scale; }
	Vector3 GetScale() const{ return mScale; }

//	void SetVertexArray(std::unique_ptr<VertexArray> vertex){ mVertexArray = std::move(vertex); }
//	const VertexArray& GetVertexArray() const { return *mVertexArray; }

	static Mesh* CreateBox(float sizeW, float sizeH, float sizeD);
	static Mesh* CreateSphere(float radius, int divWidth, int divHeight);
	static Mesh* CreateGround(int size, int rowNum);

private:
	Vector3 mPosition;
	Quaternion mRotation;
	Vector3 mScale;

	std::unique_ptr<Renderer> mRenderer;
};