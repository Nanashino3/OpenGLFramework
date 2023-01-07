//****************************************************************************
// �t�@�C�����FCell(�}�X�N���X)
// ��@���@���F2022/12/17
#ifndef _CELL_H_
#define _CELL_H_

#include "GameObject.h"
#include "../../01_Engine/Algorithm.h"

class GameParameter;
namespace tkl
{
class Mesh;
class Model;
}

class Cell : public GameObject
{
public:
	Cell(std::shared_ptr<Parameter> param);
	virtual ~Cell();

	void Initialize(const tkl::CELL& cell);

	void SetCellInfo(const tkl::CELL& cell) { mCell = cell; }
	const tkl::CELL& GetCellInfo() { return mCell; }

	virtual void Collision();
	virtual void Draw();

private:
	bool mIsSelecting;	// �J�[�\���őI�𒆂�
	tkl::CELL mCell;

	std::shared_ptr<tkl::Model> mModel;
	std::shared_ptr<tkl::Mesh> mCursor;
	std::shared_ptr<GameParameter> mParam;

	std::vector<std::shared_ptr<tkl::Mesh>> mMeshList;	// 1�}�X�ɕ����̃��b�V����o�^
};

#endif