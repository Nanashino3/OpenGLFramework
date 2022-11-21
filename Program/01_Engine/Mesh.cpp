#include "Mesh.h"

#include <vector>
#include "VertexArray.h"
#include "Camera/Camera.h"
#include "Renderer/MeshRenderer.h"
#include "Renderer/WireRenderer.h"
#include "Renderer/SpriteRenderer.h"
#include "../02_Library/Math.h"

namespace tkl
{
Mesh::Mesh()
: mPosition(tkl::Vector3(0, 0, 0))
, mRotation(tkl::Quaternion())
, mScale(tkl::Vector3(1, 1, 1))
, mRenderer(nullptr)
, mTexture(nullptr)
{}

Mesh::~Mesh()
{}

void Mesh::Draw(std::shared_ptr<Camera> camera)
{
	mRenderer->SetView(camera->GetView());
	mRenderer->SetProjection(camera->GetProjection());
	mRenderer->Draw(shared_from_this());
}

// �{�b�N�X�̍쐬
std::shared_ptr<Mesh> Mesh::CreateBox(float size)
{
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->SetRenderer(std::make_shared<MeshRenderer>());

	float sx, sy, sz;
	sx = sy = sz = size * 0.5f;
	float angles[] = {0, 90, -90, 90, -90, 180};
	tkl::Vector3 axis[] = {
		tkl::Vector3::UNITY,	// �O��
		tkl::Vector3::UNITY,	// �E��
		tkl::Vector3::UNITX,	// ���
		tkl::Vector3::UNITX,	// ����
		tkl::Vector3::UNITY,	// ����
		tkl::Vector3::UNITX		// ���
	};

	// ���_�v�Z
	std::vector<VertexArray::VERTEX> vertices;
	for(int n = 0; n < sizeof(axis) / sizeof(tkl::Vector3); ++n){
		tkl::Quaternion rot = tkl::Quaternion::RotationAxis(axis[n], tkl::ToRadian(angles[n]));

		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				tkl::Vector3 pos, norm;
				pos.mX = -sx + size * j;
				pos.mY = sy - size * i;
				pos.mZ = sz;

				pos = tkl::Vector3::TransformCoord(pos, rot);
				norm = tkl::Vector3::TransformCoord(tkl::Vector3::UNITZ, rot);

				VertexArray::VERTEX vertex = {
					pos.mX, pos.mY, pos.mZ, norm.mX, norm.mY, norm.mZ, 0, 0
				};
				vertices.emplace_back(vertex);
			}
		}
	}

	// UV���W�v�Z
	std::vector<tkl::Vector3> uv;
	for(int i = 0; i < 2; ++i){
		for(int j = 0; j < 3; ++j){
			float u0 = static_cast<float>(j) / 3.0f;
			float u1 = static_cast<float>(j + 1) / 3.0f;
			float v0 = static_cast<float>(i) / 2.0f;
			float v1 = static_cast<float>(i + 1) / 2.0f;

			tkl::Vector3 uv0 = {u0, v0, 0};
			tkl::Vector3 uv1 = {u1, v0, 0};
			tkl::Vector3 uv2 = {u0, v1, 0};
			tkl::Vector3 uv3 = {u1, v1, 0};

			uv.emplace_back(uv0);
			uv.emplace_back(uv1);
			uv.emplace_back(uv2);
			uv.emplace_back(uv3);
		}
	}
	for(int i = 0; i < vertices.size(); ++i){
		vertices[i].uv[0] = uv[i].mX;
		vertices[i].uv[1] = uv[i].mY;
	}

	// �C���f�b�N�X�v�Z(TODO�F�v�Z�ŏo������)
	int indices[] = {
		 0,  2,  3,  0,  3,  1,	// �O��
		 4,  6,  7,  4,  7,  5,	// �E��
		 8, 10, 11,  8, 11,  9,	// ���
		14, 15, 12, 15, 13, 12,	// ����
		16, 18, 19, 16, 19, 17, // ����
		22, 23, 20, 23, 21, 20	// ���
	};

	int indicesNum = sizeof(indices) / sizeof(indices[0]);
	mesh->SetVertex(std::make_shared<VertexArray>(
		static_cast<unsigned int>(vertices.size()), vertices.data(), 
		indicesNum, indices));

	return mesh;
}

// ���̂̍쐬
std::shared_ptr<Mesh> Mesh::CreateSphere(float radius, int divWidth, int divHeight)
{
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->SetRenderer(std::make_shared<MeshRenderer>());

	radius *= 0.5f;
	// ���_���W�v�Z
	std::vector<VertexArray::VERTEX> vertices;
	for(int i = 0; i < (divHeight + 1); ++i){
		float v = static_cast<float>(i) / static_cast<float>(divHeight);
		float y = cosf(tkl::PI * v) * radius;
		float r = sinf(tkl::PI * v) * radius;

		for(int j = 0; j < (divWidth + 1); ++j){
			float u = static_cast<float>(j) / static_cast<float>(divWidth);
			float x = r * cosf(2 * tkl::PI * u);
			float z = r * sinf(2 * tkl::PI * u);

			VertexArray::VERTEX vertex = {x, y, z, x, y, z, u, v};
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
	mesh->SetVertex(std::make_shared<VertexArray>(
		static_cast<unsigned int>(vertices.size()), vertices.data(),
		static_cast<unsigned int>(indices.size()), indices.data()));

	return mesh;
}

// ���ʂ̍쐬
std::shared_ptr<Mesh> Mesh::CreatePlane(float size)
{
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->SetRenderer(std::make_shared<MeshRenderer>());

	size *= 0.5f;
	VertexArray::VERTEX vertices[] = {
		{-size,  size, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f},
		{-size, -size, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f},
		{ size, -size, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f},
		{ size,  size, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f}
	};
	int indices[] = { 0, 1, 2, 0, 2, 3 };
	int indicesNum = sizeof(indices) / sizeof(indices[0]);
	mesh->SetVertex(std::make_shared<VertexArray>(4, vertices, indicesNum, indices));

	return mesh;
}

// �O���b�h�̍쐬
std::shared_ptr<Mesh> Mesh::CreateGround(int size, int rowNum)
{
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->SetRenderer(std::make_shared<WireRenderer>());

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
	mesh->SetVertex(std::make_shared<VertexArray>(gridVertex.size(), gridVertex.data(), 0, nullptr));

	return mesh;
}

// TODO�F�ʏ�̕��ʂ�Renderer���Ⴄ�����Ȃ̂œ����ɂ������ȁ[
std::shared_ptr<Mesh> Mesh::CreatePlaneForWireFrame(int size)
{
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->SetRenderer(std::make_shared<WireRenderer>());

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
	mesh->SetVertex(std::make_shared<VertexArray>(4, vertices, indicesNum, indices));

	return mesh;
}

// �e�N�X�`���p�̃��b�V���쐬
std::shared_ptr<Mesh> Mesh::CreatePlaneForTexture()
{
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->SetRenderer(std::make_shared<SpriteRenderer>());

	VertexArray::VERTEX vertices[] = {
		{-0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f,  0.0f},
		{ 0.5f,  0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f,  0.0f},
		{ 0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f,  1.0f},
		{-0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 0.0f,  1.0f}
	};

	int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	int indicesNum = sizeof(indices) / sizeof(indices[0]);
	mesh->SetVertex(std::make_shared<VertexArray>(4, vertices, indicesNum, indices));
	return mesh;
}

} // namespace tkl