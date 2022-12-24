#pragma once

namespace tkl
{
struct OBJVEC2
{
	float x, y;
	OBJVEC2(float nx = 0.0f, float ny = 0.0f);
};

struct OBJVEC3
{
	float x, y, z;
	OBJVEC3(float nx = 0.0f, float ny = 0.0f, float nz = 0.0f);
};

struct OBJVERTEX
{
	OBJVEC3 position;
	OBJVEC3 normal;
	OBJVEC2 texcoord;
	OBJVERTEX();
};

class ObjFileParser
{
public:
	ObjFileParser();
	~ObjFileParser();

	bool LoadFile(const char* filename);

	OBJVERTEX* GetVertices();
	unsigned int GetVetexNum();
	OBJVERTEX GetVertex(unsigned int value);
	unsigned int* GetIndices();
	unsigned int GetIndexNum();

private:
	OBJVERTEX* mVertices;
	unsigned int mVertexNum;

	unsigned int* mIndices;
	unsigned int mIndexNum;
};
}