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
	// 頂点配列オブジェクト
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	// 頂点バッファオブジェクト
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexNum * 8 * sizeof(float), vertices, GL_STATIC_DRAW);

	// インデックスバッファオブジェクト
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexNum * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// 頂点座標(3点)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, dimension, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

	// 法線座標(3点)
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, dimension, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(sizeof(float) * 3));

	// テクスチャ座標(2点)
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