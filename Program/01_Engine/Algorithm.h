//****************************************************************************
// �t�@�C�����FAlgorithm(�A���S���Y���N���X)
// ��@���@���F2022/11/24
#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include <vector>
#include <list>
#include "../02_Library/Vector.h"

namespace tkl
{
class Algorithm
{
public:
	enum class STATUS {
		NONE = -1,
		OPEN,		// �I�[�v��
		CLOSE,		// �N���[�Y
		START,		// �X�^�[�g
		GOAL,		// �S�[��
		EDITABLE,	// �ҏW��
		OBSTACLE,	// ��Q��

		UNEDITABLE,	// �ҏW�s��
		UNIT		// ���j�b�g
	};

	struct CELL
	{
		int row;		// �s
		int column;		// ��
		STATUS status;	// �}�X�̏��
	};

	struct NODE
	{
		CELL cell;			// �Z��
		NODE* parent;		// �e�m�[�h
		int heuristCost;	// ����R�X�g
		int betweenCost;	// �m�[�h�ԃR�X�g
		int totalCost;		// ���R�X�g
	};

	// �o�H�T��
	static bool RouteSearch(int rowSize, int colSize, std::vector<std::vector<CELL>>& cells, std::vector<CELL>& route);

private:
	static bool ASter(int rowSize, int colSize, std::vector<std::vector<NODE>>& nodes, NODE* current, std::vector<CELL>& route);
	static bool IsPossibleOpen(int rowSize, int colSize, int row, int column, std::vector<std::vector<NODE>>& nodes);

private:
	static std::list<NODE*> sOpenList;
};

using STATUS = tkl::Algorithm::STATUS;
using CELL = tkl::Algorithm::CELL;
using NODE = tkl::Algorithm::NODE;

} // namespace tkl

#endif