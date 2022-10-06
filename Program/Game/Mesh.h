#pragma once
#include <memory>

class Mesh
{
public:
	static Mesh* CreateSphere(float radius, int divWidth, int divHeight);
};