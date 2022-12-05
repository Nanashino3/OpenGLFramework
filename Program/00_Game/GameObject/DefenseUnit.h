// –h‰qƒ†ƒjƒbƒg
#ifndef _DEFENSEUNIT_H_
#define _DEFENSEUNIT_H_

#include <memory>

namespace tkl{
class Mesh;
class Camera;
class Vector3;
}

class DefenseUnit
{
public:
	DefenseUnit(const tkl::Vector3& pos);
	~DefenseUnit();

	void Update(float deltaTime, std::shared_ptr<tkl::Camera> camera);

private:
	std::shared_ptr<tkl::Mesh> mMesh;
};

#endif