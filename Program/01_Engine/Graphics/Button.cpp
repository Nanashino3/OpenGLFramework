//****************************************************************************
// �t�@�C�����FButton(�{�^���N���X)
// ��@���@���F2022/1/5
#include "Button.h"

#include "../ResourceManager.h"
#include "../Intersect.h"
#include "../Graphics/Geometry/Mesh.h"
#include "../Graphics/Geometry/Texture.h"
#include "../Graphics/Font.h"
#include "../Sound/Sound.h"

#include "../../02_Library/Input.h"
#include "../../02_Library/Vector.h"

namespace tkl
{
Button::Button(const std::string& name, const Vector3& pos, std::function<void()> onClick)
: mIsFocus(false)
, mText(name)
, mMesh(nullptr)
, mButtonOn(nullptr)
, mButtonOff(nullptr)
, mOnClick(onClick)
{
	mSound = Sound::CreateSound("Resource/sound/decide.wav");

	mMesh = Mesh::CreateMeshForSprite();
	mMesh->SetPosition(pos);

	mButtonOn = ResourceManager::GetInstance()->CreateTextureFromFile("Resource/texture/ButtonYellow.png");
	mButtonOff = ResourceManager::GetInstance()->CreateTextureFromFile("Resource/texture/ButtonBlue.png");
}

Button::~Button()
{}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�{�^���̍X�V����������
//****************************************************************************
void Button::Update()
{
	if(mIsFocus && Input::IsMouseDownTrigger(eMouse::MOUSE_LEFT)){
		if(mOnClick){
			mSound->Play();
			mOnClick();
		}
	}
	mMesh->SetTexture(mIsFocus ? mButtonOn : mButtonOff);
}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`�揈��
// ���@���Farg1 �J����
// �߂�l�F�Ȃ�
// �ځ@�ׁF�{�^���̕`�揈��������
//****************************************************************************
void Button::Draw(std::shared_ptr<Camera> camera)
{
	mMesh->Draw(camera);
	Font::DrawFontEx(mMesh->GetPosition().mX, mMesh->GetPosition().mY - 5.0f, 32, Vector3(1, 1, 1), mText.c_str());
}

//****************************************************************************
// �֐����FContainsPoint
// �T�@�v�F�{�^���͈͓̔�����
// ���@���Farg1 �}�E�X���W
// �߂�l�F�Ȃ�
// �ځ@�ׁF�{�^�����Ƀ}�E�X�|�C���^�������������m�F����
//****************************************************************************
bool Button::ContainsPoint(const Vector3& mousePos)
{
	Vector3 pos = mMesh->GetPosition();
	int textureW = mButtonOff->GetWidth();
	int textureH = mButtonOff->GetHeight();
	return tkl::IsIntersectPointRect(mousePos.mX, mousePos.mY, pos.mX, pos.mY, textureW, textureH);
}

} // namespace tkl