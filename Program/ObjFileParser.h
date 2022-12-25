#pragma once

#include <vector>
#include <string>
#include <unordered_map>

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

struct OBJMATERIAL
{
	OBJVEC3 ambient;
	OBJVEC3 diffuse;
	OBJVEC3 specular;
	std::string ambientMapName;
	std::string diffuseMapName;
	std::string specularMapName;
	std::string bumpMapName;
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

	const std::vector<std::string>& GetSubsets();
	const std::vector<int>& GetIndices(const std::string& mtlName);
	const OBJMATERIAL& GetMaterial(const std::string& mtlName);

private:
	bool ParseObjFile(const char* filename, std::vector<std::string>& mtlList);
	bool ParseMtlFile(const std::string filepath, const std::vector<std::string>& mtlList);

private:
	OBJVERTEX* mVertices;
	unsigned int mVertexNum;

	std::vector<std::string> mSubsets;
	std::unordered_map<std::string, std::vector<int>> mIndices;
	std::unordered_map<std::string, OBJMATERIAL> mCacheMaterial;
};
}