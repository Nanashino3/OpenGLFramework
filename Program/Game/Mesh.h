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

	Mesh();
	~Mesh();

	void Draw(Camera* camera);

	void SetPosition(const tkl::Vector3& pos){ mPosition = pos; }
	tkl::Vector3 GetPosition() const{ return mPosition; }

	void SetRotation(const tkl::Quaternion& rot){ mRotation = rot; }
	tkl::Quaternion GetRotation() const{ return mRotation; }

	void SetScale(const tkl::Vector3& scale){ mScale = scale; }
	tkl::Vector3 GetScale() const{ return mScale; }

	void SetRenderer(Renderer* renderer){ mRenderer = renderer; }

//	void SetVertexArray(std::unique_ptr<VertexArray> vertex){ mVertexArray = std::move(vertex); }
//	const VertexArray& GetVertexArray() const { return *mVertexArray; }

	static Mesh* CreateBox(float sizeW, float sizeH, float sizeD);
	static Mesh* CreateSphere(float radius, int divWidth, int divHeight);
	static Mesh* CreateGround(int size, int rowNum);

private:
	tkl::Vector3 mPosition;
	tkl::Quaternion mRotation;
	tkl::Vector3 mScale;

	Renderer* mRenderer;
};