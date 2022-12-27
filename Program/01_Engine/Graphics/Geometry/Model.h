#ifndef _MODEL_H_
#define _MODEL_H_

#include <memory>
#include <vector>
#include "Mesh.h"
#include "../../../02_Library/Vector.h"
#include "../../../02_Library/Quaternion.h"

namespace tkl
{
class Camera;
class Model
{
public:
	Model();
	~Model();

	void Draw(std::shared_ptr<tkl::Camera> camera);
	void AddPart(const std::shared_ptr<Mesh> part) { mParts.emplace_back(part); }

	void SetPosition(const tkl::Vector3& pos){
		mPosition = pos;
		for (int i = 0; i < mParts.size(); ++i){
			mParts[i]->SetPosition(pos);
		}
	}
	void SetRotation(const tkl::Quaternion& rot){
		mRotation = rot;
		for (int i = 0; i < mParts.size(); ++i){
			mParts[i]->SetRotation(rot);
		}
	}
	void SetScale(const tkl::Vector3& scale){
		mScale = scale;
		for (int i = 0; i < mParts.size(); ++i){
			mParts[i]->SetScale(scale);
		}
	}
	const tkl::Vector3& GetPosition() const { return mPosition; }
	const tkl::Quaternion& GetRotation() const { return mRotation; }
	const tkl::Vector3& GetScale() const { return mScale; }

	//*************************************************************
	// ÉÇÉfÉãÇÃê∂ê¨ï˚ñ@
	static std::shared_ptr<Model> CreateModelFromObjFile(const char* filepath);
	//*************************************************************
private:
	std::vector<std::shared_ptr<Mesh>> mParts;
	tkl::Vector3 mPosition;
	tkl::Quaternion mRotation;
	tkl::Vector3 mScale;
};

} // namespace tkl

#endif