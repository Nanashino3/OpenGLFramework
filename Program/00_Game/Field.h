//****************************************************************************
// �t�@�C�����FField(�t�B�[���h�N���X)
// ��@���@���F2022/12/11
#ifndef _FIELD_H_
#define _FIELD_H_

#include <memory>
#include "../01_Engine/Algorithm.h"

class Parameter;
class GameParameter;
class Field
{
	const int MAP_SIZE = 50;
public:
	Field(std::shared_ptr<Parameter> param);
	~Field();

	void Update();
	void Draw();

private:
	void UpdateMousePos();

private:
	std::shared_ptr<GameParameter> mParam;
};

#endif