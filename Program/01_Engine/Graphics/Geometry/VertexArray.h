#ifndef _VERTEXARRAY_H_
#define _VERTEXARRAY_H_

namespace tkl
{
class VertexArray
{
public:
	struct VERTEX
	{
		float position[3];
		float normal[3];
		float uv[2];
	};

	VertexArray(unsigned int vertexNum, VERTEX* vertices, unsigned int indexNum, const int* indices);
	~VertexArray();

	void Bind() const;
	void UpdateUVCoords(int vertexNum, float u, float v);

	unsigned int GetVertexNum() const{ return mVertexNum; }
	unsigned int GetIndexNum() const{ return mIndexNum; }

private:
	unsigned int mVertexNum;
	unsigned int mIndexNum;
	unsigned int mVertexArray;
	unsigned int mVertexBuffer;
	unsigned int mIndexBuffer;
	VERTEX* mVertices;
};

} // namespace tkl

#endif