#include "TestObjectFile.h"
#include "OBJLoader.h"
#include "01_Engine/Mesh.h"
#include "01_Engine/VertexArray.h"
#include "01_Engine/Renderer/MeshRenderer.h"

namespace tkl
{
std::vector<std::shared_ptr<Mesh>> TestObjectFile::CreateFromObjFile()
{
	// Objファイル読み込み用
	std::shared_ptr<OBJMESH> obj = std::make_shared<OBJMESH>();
	obj->LoadFile("Resource/obj/26F4U1-jet/F4U1_L.obj");

	std::vector<std::shared_ptr<Mesh>> createMeshs;
	OBJVERTEX* objVertices = obj->GetVertices();
	for(unsigned int i = 0; i < obj->GetNumSubsets(); ++i){
		// 登録されているサブセットを取得
		OBJSUBSET* subset = &obj->GetSubsets()[i];
//		printf("Subset\n");
//		printf(" MaterialIndex : %d\n", subset->materialIndex);
//		printf(" FaceStart : %d\n", subset->faceStart);
//		printf(" FaceCount : %d\n", subset->faceCount);

		unsigned int vtxNum = subset->faceCount;
		if(vtxNum == 0){ continue; }

		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->SetRenderer(std::make_shared<MeshRenderer>());
		std::vector<VertexArray::VERTEX> meshVertices;
		std::vector<int> meshIndices;

		unsigned int* indices = &obj->GetIndices()[subset->faceStart];
		unsigned int triangleNum = vtxNum / 3;
		for(unsigned int k = 0; k < triangleNum; ++k){
			for(unsigned int n = 0; n < 3; ++n){
				int a = (k * 3) + n;
				float px = objVertices[indices[a]].position.x;
				float py = objVertices[indices[a]].position.y;
				float pz = objVertices[indices[a]].position.z;
				float nx = objVertices[indices[a]].normal.x;
				float ny = objVertices[indices[a]].normal.y;
				float nz = objVertices[indices[a]].normal.z;
				float u  = objVertices[indices[a]].texcoord.x;
				float v  = 1.0f - objVertices[indices[a]].texcoord.y;

				VertexArray::VERTEX vertex = {px, py, pz, nx, ny, nz, u, v};
				meshVertices.emplace_back(vertex);
				meshIndices.emplace_back(a);
			}
		}

		mesh->SetVertex(std::make_shared<VertexArray>(
			static_cast<unsigned int>(meshVertices.size()), meshVertices.data(),
			static_cast<unsigned int>(meshIndices.size()), meshIndices.data()));

		createMeshs.emplace_back(mesh);
	}

	return createMeshs;
}

} // namespace tkl