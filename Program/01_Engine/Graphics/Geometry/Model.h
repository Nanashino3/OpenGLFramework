#ifndef _MODEL_H_
#define _MODEL_H_

#include <memory>
#include <vector>
#include "Mesh.h"
#include "../../../02_Library/Vector.h"

namespace tkl
{
class Camera;
class Model
{
public:
	Model();
	~Model();

	enum class eAxis {X, Y, Z};

	void Draw(std::shared_ptr<tkl::Camera> camera);

	//********************************************************
	// ëSé≤ê›íË
	void SetPosition(const tkl::Vector3& pos){
		for (int i = 0; i < mParts.size(); ++i){
			mParts[i]->SetPosition(pos);
		}
	}
	void SetRotation(const tkl::Quaternion& rot){
		for (int i = 0; i < mParts.size(); ++i){
			mParts[i]->SetRotation(rot);
		}
	}
	void SetScale(const tkl::Vector3& scale){
		for (int i = 0; i < mParts.size(); ++i){
			mParts[i]->SetScale(scale);
		}
	}
	//********************************************************

	//********************************************************
	// éwíËé≤ê›íË
	template <typename... tAxis>
	void SetPosition(const tkl::Vector3& pos, tAxis... params){
		const eAxis array[] = { static_cast<eAxis>(params)... };
		for (int i = 0; i < mParts.size(); ++i){
			tkl::Vector3 tempPos = mParts[i]->GetPosition();

			for(auto elem : array){
				switch(elem){
				case eAxis::X:
					tempPos.mX = pos.mX; break;
				case eAxis::Y:
					tempPos.mY = pos.mY; break;
				case eAxis::Z:
					tempPos.mZ = pos.mZ; break;
				}
				mParts[i]->SetRotation(tempPos);
			}
		}
	}

	template <typename... tAxis>
	void SetRotation(const tkl::Quaternion& rot, tAxis... params){
		const eAxis array[] = { static_cast<eAxis>(params)... };
		for(int i = 0; i < mParts.size(); ++i){
			tkl::Quaternion tempRotation = mParts[i]->GetRotation();

			for(auto elem : array){
				switch(elem){
				case eAxis::X:
					tempRotation.mX = rot.mX; break;
				case eAxis::Y:
					tempRotation.mY = rot.mY; break;
				case eAxis::Z:
					tempRotation.mZ = rot.mZ; break;
				}
				tempRotation.mW = rot.mW;
				mParts[i]->SetRotation(tempRotation);
			}
		}
	}

	template <typename... tAxis>
	void SetScale(const tkl::Vector3& scale, tAxis... params){
		const eAxis array[] = { static_cast<eAxis>(params)... };
		for (int i = 0; i < mParts.size(); ++i){
			tkl::Vector3 tempScale = mParts[i]->GetScale();

			for (auto elem : array) {
				switch (elem) {
				case eAxis::X:
					tempScale.mX = scale.mX; break;
				case eAxis::Y:
					tempScale.mY = scale.mY; break;
				case eAxis::Z:
					tempScale.mZ = scale.mZ; break;
				}
				mParts[i]->SetScale(tempScale);
			}
		}
	}
	//********************************************************

	void AddPart(const std::shared_ptr<Mesh> part){ mParts.emplace_back(part); }

	static std::shared_ptr<Model> CreateModelFromObjFile(const char* filepath);
private:
	std::vector<std::shared_ptr<Mesh>> mParts;
};

using eAxis = tkl::Model::eAxis;

} // namespace tkl

#endif