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
// �֐����FDraw
// �T�@�v�F�`�悷��
// ���@���F�g�p����J�����̃C���X�^���X
// �߂�l�F�Ȃ�
// �ځ@�ׁF���f���̕`��
//****************************************************************************
void Model::Draw(std::shared_ptr<tkl::Camera> camera)
{
	for(int i = 0; i < mParts.size(); ++i){
		mParts[i]->Draw(camera);
	}
}

//****************************************************************************
// �֐����FCreateModelFromObjFile
// �T�@�v�F�I�u�W�F�N�g�t�@�C�����烂�f���𐶐�����
// ���@���F�t�@�C���p�X
// �߂�l�F���f����Ԃ�
// �ځ@�ׁFObj�t�@�C�����烂�f���𐶐�����
//		 �FTODO�F�����I�ɂ͎���̉�̓N���X��K�p����
//****************************************************************************
std::shared_ptr<Model> Model::CreateModelFromObjFile(const char* filepath)
{
	// Obj�t�@�C���ǂݍ��ݗp
	std::shared_ptr<OBJMESH> obj = std::make_shared<OBJMESH>();
	if(!obj->LoadFile(filepath)){
		return nullptr;
	}

	// �t�@�C��������p�X�𕪊�����
	unsigned int endNum = std::string(filepath).find_last_of("/");
	std::string path = std::string(filepath).substr(0, endNum);

	std::shared_ptr<Model> model = std::make_shared<Model>();

	// �I�u�W�F�N�g�̃��b�V�������[�v����
	OBJVERTEX* objVertices = obj->GetVertices();
	for(unsigned int i = 0; i < obj->GetNumSubsets(); ++i){
		OBJSUBSET* subset = &obj->GetSubsets()[i];
		if(subset->faceCount == 0){ continue; }

		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->SetRenderer(std::make_shared<MeshRenderer>());

		// �}�e���A�����ݒ�
		OBJMATERIAL* mtls = &obj->GetMaterials()[subset->materialIndex];
		std::shared_ptr<Material> mtl = std::make_shared<Material>();
		mtl->SetAmbient(tkl::Vector3(mtls->ambient.x, mtls->ambient.y, mtls->ambient.z));
		mtl->SetDiffuse(tkl::Vector3(mtls->diffuse.x, mtls->diffuse.y, mtls->diffuse.z));
		mtl->SetSpecular(tkl::Vector3(mtls->specular.x, mtls->specular.y, mtls->specular.z));
		mesh->SetMaterial(mtl);

		// �e�N�X�`���ݒ�
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

		// 1Mesh���\������ʏ��
		unsigned int faceNum = subset->faceCount / TRIANGLE_NUM;

		// 1�s�ɕ����̏�񂪂���
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

		// ���_�f�[�^����ݒ�
		mesh->SetVertex(std::make_shared<VertexArray>(
			static_cast<unsigned int>(meshVertices.size()), meshVertices.data(),
			static_cast<unsigned int>(meshIndices.size()), meshIndices.data()));

		model->AddPart(mesh);
	}
	return model;
}

} // namespace tkl