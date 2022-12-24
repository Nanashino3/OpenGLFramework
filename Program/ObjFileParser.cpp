#include "ObjFileParser.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace tkl
{
OBJVEC2::OBJVEC2(float nx, float ny)
: x(nx), y(ny)
{}

OBJVEC3::OBJVEC3(float nx, float ny, float nz)
: x(nx), y(ny), z(nz)
{}

OBJVERTEX::OBJVERTEX()
: position(OBJVEC3()), normal(OBJVEC3()), texcoord(OBJVEC2())
{}

ObjFileParser::ObjFileParser()
{}

ObjFileParser::~ObjFileParser()
{}

// 指定文字で文字列を分割する
std::vector<std::string> Split(const std::string& str, char delimiter)
{
	std::vector<std::string> elems;
	std::stringstream ss(str);

	std::string value;
	while(getline(ss, value, delimiter)){
		if(!value.empty()){ 
			elems.emplace_back(value);
		}else{
			elems.emplace_back("");
		}
	}

	return elems;
}

// 指定した文字で文字列を分割し、指定した型に変換する
template <typename T>
void ParseAndConvert(T* list, const std::string& buf, char delimiter)
{
	auto splits = Split(buf, delimiter);

	int counter = 0;
	for(std::string str : splits){
		if(str.size() > 0){
			list[counter] = stoi(str);
		}
		counter++;
	}
}

bool ObjFileParser::LoadFile(const char* filename)
{
	std::ifstream ifs;
	ifs.open(filename, std::ios::in);

	if(!ifs.is_open()){
		std::cerr << "Error : open file" << filename << std::endl;
		return false;
	}

	std::vector<OBJVEC3> posList;
	std::vector<OBJVEC3> normList;
	std::vector<OBJVEC2> texList;

	std::vector<OBJVERTEX> vertices;
	std::vector<unsigned int> indices;
	unsigned int index = 0;

	std::string line;
	while(getline(ifs, line)){

		// 頂点座標
		if(line.substr(0, 2) == "v "){
			std::istringstream iss(line.substr(2));
			float vx, vy, vz;
			iss >> vx >> vy >> vz;
			posList.emplace_back(OBJVEC3(vx, vy, vz));
		}
		// 法線ベクトル
		else if(line.substr(0, 3) == "vn "){
			std::istringstream iss(line.substr(3));
			float nx, ny, nz;
			iss >> nx >> ny >> nz;
			normList.emplace_back(OBJVEC3(nx, ny, nz));
		}
		// テクスチャ座標
		else if(line.substr(0, 3) == "vt "){
			std::istringstream iss(line.substr(3));
			float tx, ty;
			iss >> tx >> ty;
			texList.emplace_back(OBJVEC2(tx, ty));
		}
		// 面情報
		else if(line.substr(0, 2) == "f "){
			size_t startNum = line.find_first_of(" ");
			std::string data = line.substr(startNum + 1, line.length());
			auto splits = Split(data, ' ');

			int vtxInfo[] = {-1, -1, -1};
			for(std::string elem : splits){
				index++;

				// 指定した文字で区切り、指定した型に変換
				ParseAndConvert<int>(vtxInfo, elem, '/');

				// 変換後データを入れ直す
				OBJVERTEX vertex;
				enum { POSITION, TEXCOORD, NORMAL, MAX_TYPE};
				for(int i = 0; i < MAX_TYPE; ++i){
					if(vtxInfo[i] == -1){ continue; }

					if(i == POSITION){
						vertex.position = posList[vtxInfo[i] - 1];
					}else if(i == TEXCOORD){
						vertex.texcoord = texList[vtxInfo[i] - 1];
					}else if(i == NORMAL){
						vertex.normal = normList[vtxInfo[i] - 1];
					}
				}
				vertices.emplace_back(vertex);
				indices.emplace_back(vertices.size() - 1);
			}
		}
	}

	// 頂点データをコピーする
	mVertexNum = vertices.size();
	mVertices = new OBJVERTEX[mVertexNum];
	for(unsigned int i = 0; i < mVertexNum; ++i){
		mVertices[i] = vertices[i];
	}

	// インデックスをコピーする
	mIndexNum = indices.size();
	mIndices = new unsigned int[mIndexNum];
	for(unsigned int i = 0; i < mIndexNum; ++i){
		mIndices[i] = indices[i];
	}

	// メモリの開放
	posList.clear();
	texList.clear();
	normList.clear();
	vertices.clear();

	return true;
}

OBJVERTEX* ObjFileParser::GetVertices()
{ return mVertices; }

unsigned int ObjFileParser::GetVetexNum()
{ return mVertexNum; }

OBJVERTEX ObjFileParser::GetVertex(unsigned int value)
{ return mVertices[value]; }

unsigned int* ObjFileParser::GetIndices()
{ return mIndices; }

unsigned int ObjFileParser::GetIndexNum()
{ return mIndexNum; }

} // namespace tkl