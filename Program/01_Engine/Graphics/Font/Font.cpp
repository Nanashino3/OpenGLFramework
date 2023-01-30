//****************************************************************************
// �t�@�C�����FFont(�t�H���g�N���X)
// ��@���@���F2022/10/22
#include "Font.h"

#include <stdarg.h>
#include "FontManager.h"
#include "../Geometry/Mesh.h"
#include "../Geometry/Texture.h"

#include "../../System.h"
#include "../../Camera/ScreenCamera.h"
#include "../../../02_Library/Utility.h"

namespace tkl
{
std::shared_ptr<Camera> Font::sCamera = nullptr;

//****************************************************************************
// �֐����FDrawStringEx
// �T�@�v�F������`��
// ���@���Farg1 �\���ʒuX
//       �Farg2 �\���ʒuY
//       �Farg3 �J���[
//       �Farg4 ������
//       �Farg5 �p�����[�^
// �߂�l�F�Ȃ�
// �ځ@�ׁF�������\������
//****************************************************************************
void Font::DrawStringEx(float x, float y, const tkl::Vector3& color, const char* str, ...)
{
	char buff[1024] = {0};
	va_list list;
	va_start(list, str);
	vsprintf_s(buff, str, list);
	va_end(list);

	int screenWidth = 0, screenHeight = 0;
	tkl::System::GetInstance()->GetWindowSize(&screenWidth, &screenHeight);
	sCamera = std::make_shared<ScreenCamera>(screenWidth, screenHeight);
	sCamera->Update();

	DrawString(x, y, buff, sCamera, color);
}

//****************************************************************************
// �֐����FDrawString(private)
// �T�@�v�F������`��
// ���@���Farg1 �\���ʒuX
//       �Farg2 �\���ʒuY
//       �Farg3 ������
//       �Farg4 �J����
//       �Farg5 �J���[
// �߂�l�F�Ȃ�
// �ځ@�ׁF�w��ʒu�Ɏw�肵���J�������g�p���ĕ������`�悷��
//****************************************************************************
void Font::DrawString(float posX, float posY, const std::string& str, std::shared_ptr<Camera> camera, const tkl::Vector3& color)
{
	wchar_t buff[256] = {0};
	tkl::ToWChara(buff, 256, str);

	float prevPosX = 0.0f;
	tkl::Character prevFont, currentFont;

	for(int i = 0; i < wcslen(buff); ++i){
		currentFont = tkl::FontManager::GetInstance()->GetFontFromCreate(buff[i]);
		std::shared_ptr<Texture> texture = currentFont.texture;
		if(texture == nullptr){ return; }
		texture->SetColor(color);

		float prevFontX = static_cast<float>(prevFont.bearing.mX * 0.5f);
		float currentFontX = static_cast<float>(currentFont.bearing.mX * 0.5f);

		// �V���������̈ʒu
		float strPosX = posX;
		float strPosY = posY;
		if(i > 0){ strPosX = prevPosX + prevFontX + currentFontX; }

		// �X�N���[�����W�ɕϊ�(���㌴�_�ɂ���)
		float screenPosX = (strPosX + (texture->GetWidth() >> 1)) - static_cast<float>(camera->GetScreenWidth() >> 1);
		float screenPosY = static_cast<float>(camera->GetScreenHeight() >> 1) - (strPosY + (texture->GetHeight() >> 1));

		// �e�N�X�`���p���b�V���ɏ���ݒ�
		std::shared_ptr<Mesh> mesh = Mesh::CreateMeshForFont();
		mesh->SetTexture(texture);
		mesh->SetPosition(tkl::Vector3(screenPosX, screenPosY, 0.0f));
		mesh->Draw(camera);

		// ���̕����ʒu�v�Z�p
		prevPosX = strPosX;
		prevFont = currentFont;
	}
}

//****************************************************************************
// �֐����FDrawFontEx
// �T�@�v�F�t�H���g�`��
// ���@���Farg1 �\���ʒuX
//       �Farg2 �\���ʒuY
//       �Farg3 �J���[
//       �Farg4 ������
//       �Farg5 �p�����[�^
// �߂�l�F�Ȃ�
// �ځ@�ׁF�ǂݍ���ł���t�H���g�ŕ�������o�͂���
//****************************************************************************
void Font::DrawFontEx(float x, float y, int fontSize, const tkl::Vector3& color, const char* str, ...)
{
	char buff[1024] = { 0 };
	va_list list;
	va_start(list, str);
	vsprintf_s(buff, str, list);
	va_end(list);

	int screenWidth = 0, screenHeight = 0;
	tkl::System::GetInstance()->GetWindowSize(&screenWidth, &screenHeight);
	sCamera = std::make_shared<ScreenCamera>(screenWidth, screenHeight);
	sCamera->Update();

	DrawFont(x, y, buff, sCamera, fontSize, color);
}

//****************************************************************************
// �֐����FDrawFont(private)
// �T�@�v�F������`��
// ���@���Farg1 �\���ʒuX
//       �Farg2 �\���ʒuY
//       �Farg3 ������
//       �Farg4 �J����
//       �Farg5 �J���[
// �߂�l�F�Ȃ�
// �ځ@�ׁF�w��ʒu�Ɏw�肵���J�������g�p���ĕ������`�悷��
//****************************************************************************
void Font::DrawFont(float posX, float posY, const std::string& str, std::shared_ptr<Camera> camera, int fontSize, const tkl::Vector3& color)
{
	// �������ɕK�v�ȏ����쐬����
	float strOffsetX = 0.0f, strOffsetY = 0.0f;
	std::vector<std::shared_ptr<Mesh>> meshList;
	for(int i = 0; i < str.length(); ++i){
		Character ch = FontManager::GetInstance()->GetFontFromTTF(str[i], fontSize);

		if(ch.texture == nullptr){ return; }

		float strPosX = posX, strPosY = posY;
		if (i > 0) {
			strPosX += ch.bearing.mX;
			strPosY -= ch.texture->GetHeight() - ch.bearing.mY;
		}

		float screenPosX = strPosX + static_cast<float>(ch.texture->GetWidth() >> 1);
		float screenPosY = strPosY + static_cast<float>(ch.texture->GetHeight() >> 1);

		std::shared_ptr<Mesh> mesh = Mesh::CreateMeshForFont();
		ch.texture->SetColor(color);
		mesh->SetTexture(ch.texture);
		mesh->SetPosition(tkl::Vector3(screenPosX, screenPosY, 0.0f));
		meshList.emplace_back(mesh);

		posX += static_cast<float>(static_cast<int>(ch.advance.mX) >> 6);
		posY += static_cast<float>(static_cast<int>(ch.advance.mY) >> 6);

		strOffsetX = std::max(strOffsetX, screenPosX);
		strOffsetY = std::max(strOffsetY, screenPosY);
	}

	// �Ō�̕����̈ʒu��������̍ŏI�Ȃ̂�
	// �e�����ɃI�t�Z�b�g���|���Đ^�񒆕`��ɂ���
	for(auto mesh : meshList){
		Vector3 pos = mesh->GetPosition();
		pos.mX -= strOffsetX * 0.5f;
		pos.mY -= strOffsetY * 0.5f;
		mesh->SetPosition(pos);

		mesh->Draw(sCamera);
	}
}

} // namespace tkl