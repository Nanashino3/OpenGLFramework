#include "Model.h"

#include "Material.h"
#include "VertexArray.h"
#include "Texture.h"
#include "OBJLoader.h"
#include "../Renderer/MeshRenderer.h"
#include "../../ResourceManager.h"

static constexpr int TRIANGLE_NUM = 3;

namespace tkl
{
Model::Model()
: mPosition(tkl::Vector3::ZERO)
, mRotation(tkl::Quaternion())
, mScale(tkl::Vector3::ZERO)
{}

Model::~Model()
{}

//****************************************************************************
// 関数名：Draw
// 概　要：描画する
// 引　数：使用するカメラのインスタンス
// 戻り値：なし
// 詳　細：モデルの描画
//****************************************************************************
void Model::Draw(std::shared_ptr<tkl::Camera> camera)
{
	for(int i = 0; i < mParts.size(); ++i){
		mParts[i]->Draw(camera);
	}
}

//****************************************************************************
// 関数名：CreateModelFromObjFile
// 概　要：オブジェクトファイルからモデルを生成する
// 引　数：ファイルパス
// 戻り値：モデルを返す
// 詳　細：Objファイルからモデルを生成する
//		 ：TODO：将来的には自作の解析クラスを適用する
//****************************************************************************
std::shared_ptr<Model> Model::CreateModelFromObjFile(const char* filepath)
{
	// Objファイル読み込み用
	std::shared_ptr<OBJMESH> obj = std::make_shared<OBJMESH>();
	if(!obj->LoadFile(filepath)){
		return nullptr;
	}

	// ファイル名からパスを分割する
	unsigned int endNum = std::string(filepath).find_last_of("/");
	std::string path = std::string(filepath).substr(0, endNum);

	std::shared_ptr<Model> model = std::make_shared<Model>();

	// オブジェクトのメッシュ分ループする
	OBJVERTEX* objVertices = obj->GetVertices();
	for(unsigned int i = 0; i < obj->GetNumSubsets(); ++i){
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
		unsigned int faceNum = subset->faceCount / TRIANGLE_NUM;

		// 1行に複数の情報がある
		std::vector<VertexArray::VERTEX> meshVertices;
		std::vector<int> meshIndices;
		unsigned int* indices = &obj->GetIndices()[subset->faceStart];
		for(unsigned int k = 0; k < faceNum; ++k){
			for(unsigned int n = 0; n < TRIANGLE_NUM; ++n){
				int idx = (k * TRIANGLE_NUM) + n;
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

		model->AddPart(mesh);
	}
	return model;
}

} // namespace tkl