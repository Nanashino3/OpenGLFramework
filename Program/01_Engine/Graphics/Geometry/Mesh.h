#ifndef _MESH_H_
#define _MESH_H_
#include <memory>
#include "../../../02_Library/Vector.h"
#include "../../../02_Library/Quaternion.h"

namespace tkl
{
class Camera;
class Renderer;
class Texture;
class Material;
class VertexArray;
class Mesh : public std::enable_shared_from_this<Mesh>
{
public:
	Mesh();
	~Mesh();

	void Draw(std::shared_ptr<Camera> camera);

	void SetAlpha(float value){ mAlpha = value; }
	float GetAlpha() const{ return mAlpha; }

	void SetPosition(const tkl::Vector3& pos){ mPosition = pos; }
	tkl::Vector3 GetPosition() const{ return mPosition; }

	void SetRotation(const tkl::Quaternion& rot){ mRotation = rot; }
	tkl::Quaternion GetRotation() const{ return mRotation; }

	void SetScale(const tkl::Vector3& scale){ mScale = scale; }
	tkl::Vector3 GetScale() const{ return mScale; }

	void SetIsWireframe(bool value){ mIsWireframe = value; }
	bool GetIsWireframe() const { return mIsWireframe; }

	void SetTexture(std::shared_ptr<Texture> tex){ mTexture = tex; }
	std::shared_ptr<Texture> GetTexture() const { return mTexture; }

	void SetVertex(std::shared_ptr<VertexArray> vertex){ mVertexArray = vertex; }
	std::shared_ptr<VertexArray> GetVertex() const { return mVertexArray; }

	void SetRenderer(std::shared_ptr<Renderer> renderer){ mRenderer = renderer; }
	std::shared_ptr<Renderer> GetRenderer() const { return mRenderer; }

	void SetMaterial(std::shared_ptr<Material> material){ mMaterial = material; }
	std::shared_ptr<Material> GetMaterial() const { return mMaterial; }

	static std::shared_ptr<Mesh> CreateBox(float size);
	static std::shared_ptr<Mesh> CreateSphere(float radius, int divWidth, int divHeight);
	static std::shared_ptr<Mesh> CreatePlane(float size);
	static std::shared_ptr<Mesh> CreateGround(int size, int rowNum);
	static std::shared_ptr<Mesh> CreatePlaneForWireFrame(int size);
	static std::shared_ptr<Mesh> CreatePlaneForTexture();

private:
	float mAlpha;
	tkl::Vector3 mPosition;
	tkl::Quaternion mRotation;
	tkl::Vector3 mScale;
	bool mIsWireframe;

	std::shared_ptr<Renderer> mRenderer;
	std::shared_ptr<Texture> mTexture;
	std::shared_ptr<VertexArray> mVertexArray;
	std::shared_ptr<Material> mMaterial;
};

} // namespace tkl

#endif