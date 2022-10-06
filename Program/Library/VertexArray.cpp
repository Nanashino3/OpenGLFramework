#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(int dimension,
	unsigned int vertexNum, const float* vertices,
	unsigned int indexNum, const int* indices)
: mVertexNum(vertexNum)
, mIndexNum(indexNum)
, mVertexArray(0)
, mVertexBuffer(0)
, mIndexBuffer(0)
{
	// ���_�z��I�u�W�F�N�g
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	// ���_�o�b�t�@�I�u�W�F�N�g
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexNum * 8 * sizeof(float), vertices, GL_STATIC_DRAW);

	// �C���f�b�N�X�o�b�t�@�I�u�W�F�N�g
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexNum * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// ���_���W(3�_)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, dimension, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

	// �@�����W(3�_)
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, dimension, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(sizeof(float) * 3));

	// �e�N�X�`�����W(2�_)
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, dimension, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(sizeof(float) * 6));
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &mVertexArray);
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
}

void VertexArray::Bind() const
{
	glBindVertexArray(mVertexArray);
}