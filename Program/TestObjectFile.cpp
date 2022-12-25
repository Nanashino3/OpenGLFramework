#include "TestObjectFile.h"

#if 1
#include "ObjFileParser.h"
#include "01_Engine/Mesh.h"
#include "01_Engine/Material.h"
#include "01_Engine/VertexArray.h"
#include "01_Engine/Renderer/MeshRenderer.h"
#include "01_Engine/ResourceManager.h"
#else
#include "OBJLoader.h"
#include "01_Engine/Mesh.h"
#include "01_Engine/VertexArray.h"
#include "01_Engine/Texture.h"
#include "01_Engine/Renderer/WireRenderer.h"
#include "01_Engine/Renderer/MeshRenderer.h"
#include "01_Engine/ResourceManager.h"
#include "02_Library/Utility.h"
#endif

namespace tkl
{
std::vector<std::shared_ptr<Mesh>> TestObjectFile::CreateFromObjFile(const char* filepath)
{
#if 1
	ObjFileParser* parser = new ObjFileParser();
	parser->LoadFile(filepath);

	std::vector<std::shared_ptr<Mesh>> createMeshs;

	OBJVERTEX* vertices = parser->GetVertices();
	std::vector<VertexArray::VERTEX> meshVertices;

	auto subsets = parser->GetSubsets();
	for(auto subset : subsets){
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->SetRenderer(std::make_shared<MeshRenderer>());

		// マテリアル情報の設定
		OBJMATERIAL mtl = parser->GetMaterial(subset);
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetAmbient(Vector3(mtl.ambient.x, mtl.ambient.y, mtl.ambient.z));
		material->SetDiffuse(Vector3(mtl.diffuse.x, mtl.diffuse.y, mtl.diffuse.z));
		mesh->SetMaterial(material);

		// 頂点データを作成
		auto indices = parser->GetIndices(subset);
		for(auto index : indices){
			OBJVERTEX vtx = parser->GetVertex(index);
			VertexArray::VERTEX vertex = { vtx.position.x, vtx.position.y, vtx.position.z,
											vtx.normal.x, vtx.normal.y, vtx.normal.z,
											vtx.texcoord.x, vtx.texcoord.y };	

			meshVertices.emplace_back(vertex);
		}
		mesh->SetVertex(std::make_shared<VertexArray>(
			static_cast<unsigned int>(meshVertices.size()), meshVertices.data(),
			static_cast<unsigned int>(indices.size()), indices.data()));

		mesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/texture/white.bmp"));
		createMeshs.emplace_back(mesh);
	}

	return createMeshs;
#else
	// Objファイル読み込み用
	std::shared_ptr<OBJMESH> obj = std::make_shared<OBJMESH>();
	obj->LoadFile(filepath);

	std::vector<std::shared_ptr<Mesh>> createMeshs;

	unsigned int a = std::string(filepath).find_last_of("/");
	std::string path = std::string(filepath).substr(0, a);

	OBJVERTEX* objVertices = obj->GetVertices();
	for(unsigned int i = 0; i < obj->GetNumSubsets(); ++i){
		// 登録されているサブセットを取得
		OBJSUBSET* subset = &obj->GetSubsets()[i];
		if(subset->faceCount == 0){ continue; }

		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->SetRenderer(std::make_shared<MeshRenderer>());

		std::shared_ptr<tkl::Texture> texture;
		OBJMATERIAL* mtls = &obj->GetMaterials()[subset->materialIndex];
		if(!std::string(mtls->ambientMapName).empty()){
			printf("AmbientMap : %s\n", mtls->ambientMapName);
			std::string temp = path + "/" + std::string(mtls->ambientMapName);
			texture = tkl::ResourceManager::GetInstance()->CreateTextureFromFile(temp.c_str());
		}else if(!std::string(mtls->specularMapName).empty()){
			printf("SpecularMap : %s\n", mtls->specularMapName);
			std::string temp = path + "/" + std::string(mtls->specularMapName);
			texture = tkl::ResourceManager::GetInstance()->CreateTextureFromFile(temp.c_str());
		}else if(!std::string(mtls->bumpMapName).empty()){
			printf("BumpMap : %s\n", mtls->bumpMapName);
			std::string temp = path + "/" + std::string(mtls->bumpMapName);
			texture = tkl::ResourceManager::GetInstance()->CreateTextureFromFile(temp.c_str());
		}else if(!std::string(mtls->diffuseMapName).empty()){
			printf("DiffuseMap : %s\n", mtls->diffuseMapName);
			std::string temp = path + "/" + std::string(mtls->diffuseMapName);
			texture = tkl::ResourceManager::GetInstance()->CreateTextureFromFile(temp.c_str());
		}
		texture = tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/texture/white.bmp");
		mesh->SetTexture(texture);

		std::vector<VertexArray::VERTEX> meshVertices;
		std::vector<int> meshIndices;

		// 1Meshを構成する面情報数
		unsigned int faceNum = subset->faceCount / 3;

		// 1行に複数の情報がある
		unsigned int* indices = &obj->GetIndices()[subset->faceStart];
		for(unsigned int k = 0; k < faceNum; ++k){
			for(unsigned int n = 0; n < 3; ++n){
				int idx = (k * 3) + n;
				OBJVERTEX vtx = obj->GetVertex(indices[idx]);
				float tx = vtx.texcoord.x * 0.8f;
				float ty = (1.0f - vtx.texcoord.y);
				VertexArray::VERTEX vertex = {	vtx.position.x, vtx.position.y, vtx.position.z, 
												vtx.normal.x, vtx.normal.y, vtx.normal.z, 
												tx, ty  };

				meshVertices.emplace_back(vertex);
				meshIndices.emplace_back(idx);
			}
		}

		mesh->SetVertex(std::make_shared<VertexArray>(
			static_cast<unsigned int>(meshVertices.size()), meshVertices.data(),
			static_cast<unsigned int>(meshIndices.size()), meshIndices.data()));

		createMeshs.emplace_back(mesh);
	}

	return createMeshs;
#endif
}

} // namespace tkl