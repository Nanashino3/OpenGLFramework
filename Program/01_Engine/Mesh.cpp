#include "Mesh.h"

#include <vector>
#include "Camera.h"
#include "VertexArray.h"
#include "MeshRenderer.h"
#include "WireRenderer.h"
#include "../02_Library/Math.h"

Mesh::Mesh()
: mPosition(tkl::Vector3(0, 0, 0))
, mRotation(tkl::Quaternion())
, mScale(tkl::Vector3(1, 1, 1))
{}

Mesh::~Mesh()
{}

void Mesh::Draw(Camera* camera)
{
	mRenderer->SetViewProjection(camera->GetViewProjection());
	mRenderer->Draw(this);
}

// �{�b�N�X�̍쐬
Mesh* Mesh::CreateBox(float size)
{
	Mesh* mesh = new Mesh();
	mesh->mRenderer = new MeshRenderer();

	size *= 0.5f;
	VertexArray::VERTEX vertices[] = {
		// ����
		{ -size, -size, -size, -1.0f,  0.0f,  0.0f },
		{ -size, -size,  size, -1.0f,  0.0f,  0.0f },
		{ -size,  size,  size, -1.0f,  0.0f,  0.0f },
		{ -size,  size, -size, -1.0f,  0.0f,  0.0f },

		// ����
		{  size, -size, -size,  0.0f,  0.0f,  -1.0f },
		{ -size, -size, -size,  0.0f,  0.0f,  -1.0f },
		{ -size,  size, -size,  0.0f,  0.0f,  -1.0f },
		{  size,  size, -size,  0.0f,  0.0f,  -1.0f },

		// ����
		{ -size, -size, -size,  0.0f, -1.0f,  0.0f },
		{  size, -size, -size,  0.0f, -1.0f,  0.0f },
		{  size, -size,  size,  0.0f, -1.0f,  0.0f },
		{ -size, -size,  size,  0.0f, -1.0f,  0.0f },

		// �E��
		{  size, -size,  size,  1.0f,  0.0f,  0.0f },
		{  size, -size, -size,  1.0f,  0.0f,  0.0f },
		{  size,  size, -size,  1.0f,  0.0f,  0.0f },
		{  size,  size,  size,  1.0f,  0.0f,  0.0f },

		// ���
		{ -size,  size, -size,  0.0f,  1.0f,  0.0f },
		{ -size,  size,  size,  0.0f,  1.0f,  0.0f },
		{  size,  size,  size,  0.0f,  1.0f,  0.0f },
		{  size,  size, -size,  0.0f,  1.0f,  0.0f },

		// �O��
		{ -size, -size,  size,  0.0f,  0.0f,  1.0f },
		{  size, -size,  size,  0.0f,  0.0f,  1.0f },
		{  size,  size,  size,  0.0f,  0.0f,  1.0f },
		{ -size,  size,  size,  0.0f,  0.0f,  1.0f }
	};

	int indices[] = {
		 0,  1,  2,  0,  2,  3,	// ����
		 4,  5,  6,  4,  6,  7,	// ����
		 8,  9, 10,  8, 10, 11,	// ����
		12, 13, 14, 12, 14, 15,	// �E��
		16, 17, 18, 16, 18, 19,	// ���
		20, 21, 22, 20, 22, 23	// �O��
	};

	int indicesNum = sizeof(indices) / sizeof(indices[0]);
	mesh->mVertexArray = std::make_unique<VertexArray>(24, vertices, indicesNum, indices);
	
	return mesh;
}

// ���̂̍쐬
Mesh* Mesh::CreateSphere(float radius, int divWidth, int divHeight)
{
	Mesh* mesh = new Mesh();
	mesh->mRenderer = new MeshRenderer();

	// ���_���W�v�Z
	std::vector<VertexArray::VERTEX> vertices;
	for(int i = 0; i < (divHeight + 1); ++i){
		float t = static_cast<float>(i) / static_cast<float>(divHeight);
		float y = cosf(tkl::PI * t) * radius;
		float r = sinf(tkl::PI * t) * radius;

		for(int j = 0; j < (divWidth + 1); ++j){
			float s = static_cast<float>(j) / static_cast<float>(divWidth);
			float x = r * cosf(2 * tkl::PI * s);
			float z = r * sinf(2 * tkl::PI * s);

			VertexArray::VERTEX vertex = {x, y, z, x, y, z};
			vertices.emplace_back(vertex);
		}
	}

	// �C���f�b�N�X�v�Z
	std::vector<int> indices;
	for(int i = 0; i < (divHeight + 1); ++i){
		for(int j = 0; j < (divWidth + 1); ++j){
			int v0 = (divWidth + 1) * i + j;	// ���_���W(����)
			int v1 = v0 + 1;					// ���_���W(�E��)
			int v2 = v1 + divWidth;				// ���_���W(����)
			int v3 = v2 + 1;					// ���_���W(�E��)

			// �����̎O�p�`
			indices.emplace_back(v0);
			indices.emplace_back(v2);
			indices.emplace_back(v3);

			// �E���̎O�p�`
			indices.emplace_back(v0);
			indices.emplace_back(v3);
			indices.emplace_back(v1);
		}
	}
	mesh->mVertexArray = std::make_unique<VertexArray>(
		static_cast<unsigned int>(vertices.size()), vertices.data(),
		static_cast<unsigned int>(indices.size()), indices.data());

	return mesh;
}

// ���ʂ̍쐬
Mesh* Mesh::CreatePlane(float size)
{
	Mesh* mesh = new Mesh();
	mesh->mRenderer = new MeshRenderer();

	size *= 0.5f;

	VertexArray::VERTEX vertices[] = {
		{-size,  size, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
		{ size,  size, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f},
		{ size, -size, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f},
		{-size, -size, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f}
	};
	int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	int indicesNum = sizeof(indices) / sizeof(indices[0]);
	mesh->mVertexArray = std::make_unique<VertexArray>(4, vertices, indicesNum, indices);

	return mesh;
}

// �O���b�h�̍쐬
Mesh* Mesh::CreateGround(int size, int rowNum)
{
	Mesh* mesh = new Mesh();
	mesh->mRenderer = new WireRenderer();

	float l = size * rowNum * 0.5f;
	float n = -l;

	VertexArray::VERTEX v[4] = { 0.0f };
	std::vector<VertexArray::VERTEX> gridVertex;

	for (int i = 0; i < rowNum + 1; ++i) {
		if ((rowNum >> 1) == i) {
			v[0] = {  n,  0,  l,  1.0f,  0.0f,  0.0f };
			v[1] = {  n,  0, -l,  1.0f,  0.0f,  0.0f };
			v[2] = {  l,  0,  n,  0.0f,  0.0f,  1.0f };
			v[3] = { -l,  0,  n,  0.0f,  0.0f,  1.0f };
		}
		else {
			v[0] = {  n,  0,  l,  1.0f,  1.0f,  1.0f };
			v[1] = {  n,  0, -l,  1.0f,  1.0f,  1.0f };
			v[2] = {  l,  0,  n,  1.0f,  1.0f,  1.0f };
			v[3] = { -l,  0,  n,  1.0f,  1.0f,  1.0f };
		}

		gridVertex.emplace_back(v[0]);
		gridVertex.emplace_back(v[1]);
		gridVertex.emplace_back(v[2]);
		gridVertex.emplace_back(v[3]);

		n += size;
	}

	VertexArray::VERTEX v5 = { 0.0f,   l,  0.0f,  0.0f,  1.0f,  0.0f };
	VertexArray::VERTEX v6 = { 0.0f,  -l,  0.0f,  0.0f,  1.0f,  0.0f };

	gridVertex.emplace_back(v5);
	gridVertex.emplace_back(v6);
	mesh->mVertexArray = std::make_unique<VertexArray>(gridVertex.size(), gridVertex.data(), 0, nullptr);

	return mesh;
}