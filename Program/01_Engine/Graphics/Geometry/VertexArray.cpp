#include "VertexArray.h"
#include <cmath>
#include <GL/glew.h>

namespace tkl
{
VertexArray::VertexArray(unsigned int vertexNum, VERTEX* vertices, unsigned int indexNum, const int* indices)
: mVertexNum(vertexNum)
, mIndexNum(indexNum)
, mVertexArray(0)
, mVertexBuffer(0)
, mIndexBuffer(0)
, mVertices(vertices)
{
	// ���_�z��I�u�W�F�N�g
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	// ���_�o�b�t�@�I�u�W�F�N�g
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexNum * sizeof(VERTEX), vertices, GL_DYNAMIC_DRAW);

	// �C���f�b�N�X�o�b�t�@�I�u�W�F�N�g
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexNum * sizeof(int), indices, GL_STATIC_DRAW);

	// ���_���W(3�_)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX), static_cast<VERTEX*>(0)->position);

	// �@�����W(3�_)
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX), static_cast<VERTEX*>(0)->normal);

	// �e�N�X�`�����W(2�_)
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX), static_cast<VERTEX*>(0)->uv);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::Bind() const
{
	glBindVertexArray(mVertexArray);
}

// UV���W�̍X�V
void VertexArray::UpdateUVCoords(int vertexNum, float u, float v)
{
	mVertices[vertexNum].uv[0] = u;
	mVertices[vertexNum].uv[1] = v;

    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(VERTEX) * vertexNum + offsetof(VERTEX, uv), sizeof(float) * 2, mVertices[vertexNum].uv);
}

} // namespace tkl