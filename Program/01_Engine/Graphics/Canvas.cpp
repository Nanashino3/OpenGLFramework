//****************************************************************************
// �t�@�C�����FCanvas(�L�����o�X�N���X)
// ��@���@���F2022/1/5
#include "Canvas.h"
#include "Button.h"

#include "../System.h"
#include "../../02_Library/Input.h"
#include "../../02_Library/Vector.h"

#include <iostream>

namespace tkl
{
Canvas::Canvas()
: mScreenW(0), mScreenH(0)
{
	tkl::System::GetInstance()->GetWindowSize(&mScreenW, &mScreenH);
}

Canvas::~Canvas()
{}

//****************************************************************************
// �֐����FAddButton
// �T�@�v�F�{�^���ǉ�
// ���@���Farg1 �{�^����
//       �Farg2 �\���ʒu
//       �Farg3 �N���b�N�������̏���
// �߂�l�F�Ȃ�
// �ځ@�ׁF�L�����o�X�Ƀ{�^����ǉ�����
//****************************************************************************
void Canvas::AddButton(const std::string& name, const Vector3& pos, std::function<void()> onClick)
{
	std::shared_ptr<Button> btn = std::make_shared<Button>(name, pos, onClick);
	mButtons.emplace_back(btn);
}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�L�����o�X�̍X�V����������
//****************************************************************************
void Canvas::Update()
{
	if(mButtons.empty()){ return; }

	int mousePosX = 0, mousePosY = 0;
	tkl::Input::GetMousePoint(&mousePosX, &mousePosY);
	mousePosX = mousePosX - (mScreenW >> 1);
	mousePosY = (mScreenH >> 1) - mousePosY;

	for(auto button : mButtons){
		button->SetIsFocus(false);
		if(button->ContainsPoint(tkl::Vector3(mousePosX, mousePosY, 0))){
			button->SetIsFocus(true);
		}

		button->Update();
	}
}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`�揈��
// ���@���Farg1 �J����
// �߂�l�F�Ȃ�
// �ځ@�ׁF�L�����o�X�̕`�揈��������
//****************************************************************************
void Canvas::Draw(std::shared_ptr<Camera> camera)
{
	for (auto button : mButtons) {
		button->Draw(camera);
	}
}

} // namespace tkl