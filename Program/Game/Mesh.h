#pragma once
#include <memory>

class VertexArray;
class Mesh
{
public:
	static Mesh* CreateSphere(float radius, int divWidth, int divHeight);

	std::unique_ptr<VertexArray> mVertexArray;
};