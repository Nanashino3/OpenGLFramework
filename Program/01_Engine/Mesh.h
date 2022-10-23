#pragma once
#include <memory>
#include "../02_Library/Vector.h"
#include "../02_Library/Matrix.h"
#include "../02_Library/Quaternion.h"

class Camera;
class Renderer;
class VertexArray;
class Mesh
{
public:
	Mesh();
	~Mesh();

	void Draw(Camera* camera);

	void SetPosition(const tkl::Vector3& pos){ mPosition = pos; }
	tkl::Vector3 GetPosition() const{ return mPosition; }

	void SetRotation(const tkl::Quaternion& rot){ mRotation = rot; }
	tkl::Quaternion GetRotation() const{ return mRotation; }

	void SetScale(const tkl::Vector3& scale){ mScale = scale; }
	tkl::Vector3 GetScale() const{ return mScale; }

	static Mesh* CreateBox(float size);
	static Mesh* CreateSphere(float radius, int divWidth, int divHeight);
	static Mesh* CreateGround(int size, int rowNum);

	std::unique_ptr<VertexArray> mVertexArray;
private:
	tkl::Vector3 mPosition;
	tkl::Quaternion mRotation;
	tkl::Vector3 mScale;

	Renderer* mRenderer;
};