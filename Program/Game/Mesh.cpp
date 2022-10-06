#include "Mesh.h"

#include <math.h>
#include <vector>
#include "VertexArray.h"
#include "../Library/Vector.h"
#include "../Library/Math.h"

// 球体の作成
Mesh* Mesh::CreateSphere(float radius, int divWidth, int divHeight)
{
	Mesh* mesh = new Mesh();
	// 頂点座標計算
	std::vector<VertexArray::VERTEX> vertices;
	for(int i = 0; i < (divHeight + 1); ++i){
		float t = static_cast<float>(i) / static_cast<float>(divHeight);
		float y = cosf(tkl::PI * t) * radius;
		float r = sinf(tkl::PI * t) * radius;

		for(int j = 0; j < (divWidth + 1); ++j){
			float s = static_cast<float>(j) / static_cast<float>(divWidth);
			float x = r * cosf(2 * tkl::PI * s);
			float z = r * sinf(2 * tkl::PI * s);

			VertexArray::VERTEX vertex = {x, y, z};
			vertices.emplace_back(vertex);
		}
	}

	// インデックス計算
	std::vector<int> indices;
	for(int i = 0; i < (divHeight + 1); ++i){
		for(int j = 0; j < (divWidth + 1); ++j){
			int v0 = (divHeight + 1) * i + j;	// 頂点座標(左上)
			int v1 = v0 + 1;					// 頂点座標(右上)
			int v2 = v1 + divWidth;				// 頂点座標(左下)
			int v3 = v2 + 1;					// 頂点座標(右下)

			// 左下の三角形
			indices.emplace_back(v0);
			indices.emplace_back(v2);
			indices.emplace_back(v3);

			// 右下の三角形
			indices.emplace_back(v0);
			indices.emplace_back(v3);
			indices.emplace_back(v1);
		}
	}

	mesh->mVertexArray = std::make_unique<VertexArray>(3,
		static_cast<unsigned int>(vertices.size()), vertices.data(),
		static_cast<unsigned int>(indices.size()), indices.data());

	return mesh;
}