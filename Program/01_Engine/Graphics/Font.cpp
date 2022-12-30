//****************************************************************************
// �t�@�C�����FFont(�t�H���g�N���X)
// ��@���@���F2022/10/22
#include "Font.h"

#include <stdarg.h>
#include "FontManager.h"
#include "Geometry/Mesh.h"
#include "Geometry/Texture.h"

#include "../System.h"
#include "../Camera/ScreenCamera.h"
#include "../../02_Library/Utility.h"

namespace tkl
{
std::shared_ptr<Mesh> Font::sMesh = nullptr;
std::shared_ptr<Camera> Font::sCamera = nullptr;

//****************************************************************************
// �֐����FDrawFontEx
// �T�@�v�F�t�H���g�`��
// ���@���Farg1 �\���ʒuX
//       �Farg2 �\���ʒuY
//       �Farg3 ������
//       �Farg4 �p�����[�^
// �߂�l�F�Ȃ�
// �ځ@�ׁF�ǂݍ���ł���t�H���g�ŕ�������o�͂���
//****************************************************************************
void Font::DrawFontEx(float x, float y, float scale, const char* str, ...)
{
	char buff[1024] = { 0 };
	va_list list;
	va_start(list, str);
	vsprintf_s(buff, str, list);
	va_end(list);

	sMesh = Mesh::CreatePlaneForTexture();

	int screenWidth = 0, screenHeight = 0;
	tkl::System::GetInstance()->GetWindowSize(&screenWidth, &screenHeight);
	sCamera = std::make_shared<ScreenCamera>(screenWidth, screenHeight);
	sCamera->Update();

	for(int i = 0; i < std::string(buff).length(); ++i){
		tkl::Character ch = tkl::FontManager::GetInstance()->GetFontFromTTF(buff[i]);

		if(ch.texture == nullptr){ return; }

		float strPosX = x + ch.bearing.mX;
		float strPosY = y - (ch.texture->GetHeight() - ch.bearing.mY);

 		float screenPosX = (strPosX + (ch.texture->GetWidth() >> 1)) / static_cast<float>(sCamera->GetScreenWidth() >> 1);
		float screenPosY = (strPosY + (ch.texture->GetHeight() >> 1)) / static_cast<float>(sCamera->GetScreenHeight() >> 1);

		sMesh->SetTexture(ch.texture);
		sMesh->SetPosition(tkl::Vector3(screenPosX, screenPosY, 0));
		sMesh->Draw(sCamera);

		x += (static_cast<int>(ch.advance.mX) >> 6);
		y += (static_cast<int>(ch.advance.mY) >> 6);
	}
}

//****************************************************************************
// �֐����FDrawStringEx
// �T�@�v�F������`��
// ���@���Farg1 �\���ʒuX
//       �Farg2 �\���ʒuY
//       �Farg3 ������
//       �Farg4 �p�����[�^
// �߂�l�F�Ȃ�
// �ځ@�ׁF�������\������
//****************************************************************************
void Font::DrawStringEx(float x, float y, const char* str, ...)
{
	char buff[1024] = {0};
	va_list list;
	va_start(list, str);
	vsprintf_s(buff, str, list);
	va_end(list);

	sMesh = Mesh::CreatePlaneForTexture();
	
	int screenWidth = 0, screenHeight = 0;
	tkl::System::GetInstance()->GetWindowSize(&screenWidth, &screenHeight);
	sCamera = std::make_shared<ScreenCamera>(screenWidth, screenHeight);
	sCamera->Update();

	DrawString(x, y, buff, sCamera);
}

//****************************************************************************
// �֐����FDrawString(private)
// �T�@�v�F������`��
// ���@���Farg1 �\���ʒuX
//       �Farg2 �\���ʒuY
//       �Farg3 ������
//       �Farg4 �J����
// �߂�l�F�Ȃ�
// �ځ@�ׁF�w��ʒu�Ɏw�肵���J�������g�p���ĕ������`�悷��
//****************************************************************************
void Font::DrawString(float posX, float posY, const std::string& str, std::shared_ptr<Camera> camera)
{
	wchar_t buff[256] = {0};
	tkl::ToWChara(buff, 256, str);

	float prevPosX = 0.0f;
	tkl::Character prevFont, currentFont;

	for(int i = 0; i < wcslen(buff); ++i){
		currentFont = tkl::FontManager::GetInstance()->GetFontFromCreate(buff[i]);
		std::shared_ptr<Texture> texture = currentFont.texture;
		float prevFontX = static_cast<float>(prevFont.bearing.mX * 0.5f);
		float currentFontX = static_cast<float>(currentFont.bearing.mX * 0.5f);

		// �V���������̈ʒu
		float strPosX = posX;
		float strPosY = posY;
		if(i > 0){ strPosX = prevPosX + prevFontX + currentFontX; }

		// �X�N���[�����W�ɕϊ�(���㌴�_�ɂ���)
		float screenPosX = (strPosX + texture->GetWidth() * 0.5f) / static_cast<float>(camera->GetScreenWidth() * 0.5f) - 1.0f;
		float screenPoxY = 1.0f - (strPosY + texture->GetHeight() * 0.5f) / static_cast<float>(camera->GetScreenHeight() * 0.5f);

		// �e�N�X�`���p���b�V���ɏ���ݒ�
		sMesh->SetTexture(texture);
		sMesh->SetPosition(tkl::Vector3(screenPosX, screenPoxY, 0.0f));
		sMesh->Draw(camera);

		// ���̕����ʒu�v�Z�p
		prevPosX = strPosX;
		prevFont = currentFont;
	}
}

} // namespace tkl