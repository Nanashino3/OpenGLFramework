#include "Mesh.h"

#include <vector>
#include "Camera.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "../Library/Math.h"
#include "../Library/Matrix.h"

Mesh::Mesh()
: mPosition(Vector3(0, 0, 0))
, mRotation(Quaternion())
, mScale(Vector3(1, 1, 1))
{
	mRenderer = new Renderer();
	mRenderer->Initialize();
}

void Mesh::Render(Camera* camera)
{
	mRenderer->SetViewProjectionMatrix(camera->GetViewProjection());

	Matrix worldTransform;
	worldTransform  = Matrix::CreateTranslation(mPosition);
	worldTransform *= Matrix::CreateRotationFromQuaternion(mRotation);
	worldTransform *= Matrix::CreateScale(mScale);
	mRenderer->SetWorldTransformMatrix(worldTransform);

	mRenderer->Draw(mVertexArray.get());
}

Mesh* Mesh::CreateBox(float sizeW, float sizeH, float sizeD)
{
	Mesh* mesh = new Mesh();
	VertexArray::VERTEX vertices[] = {
		// ����
		{ -25.0f, -25.0f, -25.0f, -1.0f,  0.0f,  0.0f },
		{ -25.0f, -25.0f,  25.0f, -1.0f,  0.0f,  0.0f },
		{ -25.0f,  25.0f,  25.0f, -1.0f,  0.0f,  0.0f },
		{ -25.0f,  25.0f, -25.0f, -1.0f,  0.0f,  0.0f },

		// ����
		{  25.0f, -25.0f, -25.0f,  0.0f,  0.0f,  -1.0f },
		{ -25.0f, -25.0f, -25.0f,  0.0f,  0.0f,  -1.0f },
		{ -25.0f,  25.0f, -25.0f,  0.0f,  0.0f,  -1.0f },
		{  25.0f,  25.0f, -25.0f,  0.0f,  0.0f,  -1.0f },

		// ����
		{ -25.0f, -25.0f, -25.0f,  0.0f, -1.0f,  0.0f },
		{  25.0f, -25.0f, -25.0f,  0.0f, -1.0f,  0.0f },
		{  25.0f, -25.0f,  25.0f,  0.0f, -1.0f,  0.0f },
		{ -25.0f, -25.0f,  25.0f,  0.0f, -1.0f,  0.0f },

		// �E��
		{  25.0f, -25.0f,  25.0f,  1.0f,  0.0f,  0.0f },
		{  25.0f, -25.0f, -25.0f,  1.0f,  0.0f,  0.0f },
		{  25.0f,  25.0f, -25.0f,  1.0f,  0.0f,  0.0f },
		{  25.0f,  25.0f,  25.0f,  1.0f,  0.0f,  0.0f },

		// ���
		{ -25.0f,  25.0f, -25.0f,  0.0f,  1.0f,  0.0f },
		{ -25.0f,  25.0f,  25.0f,  0.0f,  1.0f,  0.0f },
		{  25.0f,  25.0f,  25.0f,  0.0f,  1.0f,  0.0f },
		{  25.0f,  25.0f, -25.0f,  0.0f,  1.0f,  0.0f },

		// �O��
		{ -25.0f, -25.0f,  25.0f,  0.0f,  0.0f,  1.0f },
		{  25.0f, -25.0f,  25.0f,  0.0f,  0.0f,  1.0f },
		{  25.0f,  25.0f,  25.0f,  0.0f,  0.0f,  1.0f },
		{ -25.0f,  25.0f,  25.0f,  0.0f,  0.0f,  1.0f }
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
	mesh->mVertexArray = std::make_unique<VertexArray>(3, 24, vertices, indicesNum, indices);

	return mesh;
}

// ���̂̍쐬
Mesh* Mesh::CreateSphere(float radius, int divWidth, int divHeight)
{
	Mesh* mesh = new Mesh();
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
			int v0 = (divHeight + 1) * i + j;	// ���_���W(����)
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

	mesh->mVertexArray = std::make_unique<VertexArray>(3,
		static_cast<unsigned int>(vertices.size()), vertices.data(),
		static_cast<unsigned int>(indices.size()), indices.data());

	return mesh;
}