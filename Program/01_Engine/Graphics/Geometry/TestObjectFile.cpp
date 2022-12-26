#include "TestObjectFile.h"

#include "OBJLoader.h"
#include "Mesh.h"
#include "Material.h"
#include "VertexArray.h"
#include "Texture.h"
#include "../Renderer/MeshRenderer.h"
#include "../../ResourceManager.h"

namespace tkl
{
std::vector<std::shared_ptr<Mesh>> TestObjectFile::CreateFromObjFile(const char* filepath)
{
	// Objファイル読み込み用
	std::shared_ptr<OBJMESH> obj = std::make_shared<OBJMESH>();
	obj->LoadFile(filepath);

	std::vector<std::shared_ptr<Mesh>> createMeshs;

	unsigned int endNum = std::string(filepath).find_last_of("/");
	std::string path = std::string(filepath).substr(0, endNum);

	OBJVERTEX* objVertices = obj->GetVertices();
	for(unsigned int i = 0; i < obj->GetNumSubsets(); ++i){
		// 登録されているサブセットを取得
		OBJSUBSET* subset = &obj->GetSubsets()[i];
		if(subset->faceCount == 0){ continue; }

		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->SetRenderer(std::make_shared<MeshRenderer>());

		// マテリアル情報設定
		OBJMATERIAL* mtls = &obj->GetMaterials()[subset->materialIndex];
		std::shared_ptr<Material> mtl = std::make_shared<Material>();
		mtl->SetAmbient(tkl::Vector3(mtls->ambient.x, mtls->ambient.y, mtls->ambient.z));
		mtl->SetDiffuse(tkl::Vector3(mtls->diffuse.x, mtls->diffuse.y, mtls->diffuse.z));
		mtl->SetSpecular(tkl::Vector3(mtls->specular.x, mtls->specular.y, mtls->specular.z));
		mesh->SetMaterial(mtl);

		// テクスチャ設定
		std::shared_ptr<tkl::Texture> texture;
		if(!std::string(mtls->ambientMapName).empty()){
			std::string imgFile = path + "/" + std::string(mtls->ambientMapName);
			texture = tkl::ResourceManager::GetInstance()->CreateTextureFromFile(imgFile.c_str());
		}else if(!std::string(mtls->specularMapName).empty()){
			std::string imgFile = path + "/" + std::string(mtls->specularMapName);
			texture = tkl::ResourceManager::GetInstance()->CreateTextureFromFile(imgFile.c_str());
		}else if(!std::string(mtls->bumpMapName).empty()){
			std::string imgFile = path + "/" + std::string(mtls->bumpMapName);
			texture = tkl::ResourceManager::GetInstance()->CreateTextureFromFile(imgFile.c_str());
		}else if(!std::string(mtls->diffuseMapName).empty()){
			std::string imgFile = path + "/" + std::string(mtls->diffuseMapName);
			texture = tkl::ResourceManager::GetInstance()->CreateTextureFromFile(imgFile.c_str());
		}
		if(texture == nullptr){ texture = tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/texture/white.bmp"); }
		mesh->SetTexture(texture);

		// 1Meshを構成する面情報数
		unsigned int faceNum = subset->faceCount / 3;

		// 1行に複数の情報がある
		std::vector<VertexArray::VERTEX> meshVertices;
		std::vector<int> meshIndices;
		unsigned int* indices = &obj->GetIndices()[subset->faceStart];
		for(unsigned int k = 0; k < faceNum; ++k){
			for(unsigned int n = 0; n < 3; ++n){
				int idx = (k * 3) + n;
				OBJVERTEX vtx = obj->GetVertex(indices[idx]);
				VertexArray::VERTEX vertex = {	vtx.position.x, vtx.position.y, vtx.position.z, 
												vtx.normal.x, vtx.normal.y, vtx.normal.z, 
												vtx.texcoord.x, 1.0f - vtx.texcoord.y };

				meshVertices.emplace_back(vertex);
				meshIndices.emplace_back(idx);
			}
		}

		// 頂点データ等を設定
		mesh->SetVertex(std::make_shared<VertexArray>(
			static_cast<unsigned int>(meshVertices.size()), meshVertices.data(),
			static_cast<unsigned int>(meshIndices.size()), meshIndices.data()));

		createMeshs.emplace_back(mesh);
	}

	return createMeshs;
}

} // namespace tkl