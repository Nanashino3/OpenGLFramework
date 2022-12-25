#include "ObjFileParser.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace tkl
{
//**********************************************************************
// 指定文字で文字列を分割する
std::vector<std::string> Split(const std::string& str, char delimiter)
{
	std::vector<std::string> elems;
	std::stringstream ss(str);

	std::string value;
	while (getline(ss, value, delimiter)) {
		if (!value.empty()) {
			elems.emplace_back(value);
		}
		else {
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
	for (std::string str : splits) {
		if (str.size() > 0) {
			list[counter] = stoi(str);
		}
		counter++;
	}
}
//**********************************************************************

//**********************************************************************
// OBJVEC2
OBJVEC2::OBJVEC2(float nx, float ny)
: x(nx), y(ny)
{}
//**********************************************************************

//**********************************************************************
// OBJVEC3
OBJVEC3::OBJVEC3(float nx, float ny, float nz)
: x(nx), y(ny), z(nz)
{}
//**********************************************************************

//**********************************************************************
// OBJVERTEX
OBJVERTEX::OBJVERTEX()
: position(OBJVEC3()), normal(OBJVEC3()), texcoord(OBJVEC2())
{}
//**********************************************************************

ObjFileParser::ObjFileParser()
{}

ObjFileParser::~ObjFileParser()
{}

// TODO：三角形で構成されていれば表示できる
bool ObjFileParser::LoadFile(const char* filename)
{
	// オブジェクトファイルの解析
	std::vector<std::string> mtlList;
	if(!ParseObjFile(filename, mtlList)){
		return false;
	}

	// ファイルパスを求める
	size_t length = std::string(filename).find_last_of('/');
	std::string filepath = std::string(filename).substr(0, length);

	// マテリアルファイルの解析
	if(!ParseMtlFile(filepath, mtlList)){
		return false;	
	}

	return true;
}

// Objファイルを解析
bool ObjFileParser::ParseObjFile(const char* filename, std::vector<std::string>& mtlList)
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

	std::string line = "", mtlName = "";
	while(getline(ifs, line)){

		// 頂点座標をまとめる
		if(line.substr(0, 2) == "v "){
			std::istringstream iss(line.substr(2));
			float vx, vy, vz;
			iss >> vx >> vy >> vz;
			posList.emplace_back(OBJVEC3(vx, vy, vz));
		}
		// 法線ベクトルをまとめる
		else if(line.substr(0, 3) == "vn "){
			std::istringstream iss(line.substr(3));
			float nx, ny, nz;
			iss >> nx >> ny >> nz;
			normList.emplace_back(OBJVEC3(nx, ny, nz));
		}
		// テクスチャ座標をまとめる
		else if(line.substr(0, 3) == "vt "){
			std::istringstream iss(line.substr(3));
			float tx, ty;
			iss >> tx >> ty;
			texList.emplace_back(OBJVEC2(tx, ty));
		}
		// 面情報から頂点データを作成しまとめる
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
				mIndices[mtlName].emplace_back(vertices.size() - 1);
			}
		}
		// 読み込むマテリアルファイル
		else if(line.substr(0, 7) == "mtllib "){
			size_t startNum = line.find_first_of(" ");
			std::string data = line.substr(startNum + 1, line.length());
			mtlList.emplace_back(data);
		}
		// 使用するマテリアルファイル
		else if(line.substr(0, 7) == "usemtl "){
			size_t startNum = line.find_first_of(" ");
			mtlName = line.substr(startNum + 1, line.length());
			mSubsets.emplace_back(mtlName);
		}
	}
	ifs.close();

	// 頂点データをコピーする
	mVertexNum = vertices.size();
	mVertices = new OBJVERTEX[mVertexNum];
	for(unsigned int i = 0; i < mVertexNum; ++i){
		mVertices[i] = vertices[i];
	}

	// メモリの開放
	posList.clear();
	texList.clear();
	normList.clear();
	vertices.clear();

	return true;
}

// マテリアルファイルの解析
bool ObjFileParser::ParseMtlFile(const std::string filepath, const std::vector<std::string>& mtlList)
{
	for(std::string filename : mtlList){
		std::string mtlFile = filepath + "/" + filename;

		std::ifstream ifs;
		ifs.open(mtlFile, std::ios::in);

		if(!ifs.is_open()){
			std::cerr << "Error : open file" << filename << std::endl;
			return false;
		}

		// 1行ずつ解析
		std::string line = "", mtlName = "";
		while(getline(ifs, line)){
			if(line.substr(0, 7) == "newmtl "){
				size_t length = line.find_first_of(' ');
				mtlName = line.substr(length + 1, line.length());
			}
			// ambientカラー
			else if(line.substr(0, 3) == "Ka "){
				std::istringstream iss(line.substr(3));

				float r, g, b;
				iss >> r >> g >> b;
				mCacheMaterial[mtlName].ambient = OBJVEC3(r, g, b);
			}
			// diffuseカラー
			else if(line.substr(0, 3) == "Kd "){
				std::istringstream iss(line.substr(3));

				float r, g, b;
				iss >> r >> g >> b;
				mCacheMaterial[mtlName].diffuse = OBJVEC3(r, g, b);
			}
			// ambientテクスチャマップ
			else if(line.substr(0, 6) == "map_Ka"){
				size_t length = line.find_first_of(' ');
				std::string imgName = line.substr(length + 1, line.length());
				std::string imgFile = filepath + "/" + imgName;
				mCacheMaterial[mtlName].ambientMapName = imgFile;
			}
			// diffuseテクスチャマップ
			else if(line.substr(0, 6) == "map_Kd"){
				size_t length = line.find_first_of(' ');
				std::string imgName = line.substr(length + 1, line.length());
				std::string imgFile = filepath + "/" + imgName;
				mCacheMaterial[mtlName].diffuseMapName = imgFile;
			}
			// specularテクスチャマップ
			else if(line.substr(0, 6) == "map_Ns"){
				size_t length = line.find_first_of(' ');
				std::string imgName = line.substr(length + 1, line.length());
				std::string imgFile = filepath + "/" + imgName;
				mCacheMaterial[mtlName].specularMapName = imgFile;
			}
			// bumpテクスチャマップ
			else if(line.substr(0, 6) == "map_bump"){
				size_t length = line.find_first_of(' ');
				std::string imgName = line.substr(length + 1, line.length());
				std::string imgFile = filepath + "/" + imgName;
				mCacheMaterial[mtlName].bumpMapName = imgFile;
			}
		}

		ifs.close();
	}
}

OBJVERTEX* ObjFileParser::GetVertices()
{ return mVertices; }

unsigned int ObjFileParser::GetVetexNum()
{ return mVertexNum; }

OBJVERTEX ObjFileParser::GetVertex(unsigned int value)
{ return mVertices[value]; }

const std::vector<std::string>& ObjFileParser::GetSubsets()
{ return mSubsets; }

const std::vector<int>& ObjFileParser::GetIndices(const std::string& mtlName)
{ return mIndices[mtlName]; }

const OBJMATERIAL& ObjFileParser::GetMaterial(const std::string& mtlName)
{ return mCacheMaterial[mtlName]; }

} // namespace tkl