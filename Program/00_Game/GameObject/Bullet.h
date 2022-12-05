#ifndef _BULLET_H_
#define _BULLET_H_

#include <memory>
namespace tkl {
class Mesh;
class Camera;
class Vector3;
}

class Bullet
{
public:
	Bullet(const tkl::Vector3& pos);
	~Bullet();

	void Update(float deltaTime, std::shared_ptr<tkl::Camera> camera);

private:
	std::shared_ptr<tkl::Mesh> mMesh;
};

#endif