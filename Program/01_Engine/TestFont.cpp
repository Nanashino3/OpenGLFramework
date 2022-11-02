#include "TestFont.h"

#include "Mesh.h"
#include "FontManager.h"
#include "Camera/Camera.h"
#include "../02_Library/Utility.h"

namespace tkl
{
// TODO�F�ꕔ�̕��������܂��\���ł��Ȃ���肠��(������)
void DrawString(float posX, float posY, const std::string& str, std::shared_ptr<Camera> camera)
{
	wchar_t buff[256] = {0};
	tkl::ToWChara(buff, 256, str);

	tkl::FontManager* manager = tkl::FontManager::GetInstance();
	std::shared_ptr<Mesh> mesh = Mesh::CreatePlaneForTexture();

	float prevPosX = 0.0f;
	tkl::FontManager::Font prevFont = { nullptr, 0, 0 }, currentFont = { nullptr, 0, 0 };
	for(int i = 0; i < wcslen(buff); ++i){
		currentFont = manager->GetFontTexture(buff[i]);
		float prevFontX = static_cast<float>(prevFont.strWidth * 0.5f);
		float currentFontX = static_cast<float>(currentFont.strWidth * 0.5f);

		// �V���������̈ʒu
		float strPosX = posX;
		float strPosY = posY;
		if(i > 0){
			strPosX += prevPosX + prevFontX + currentFontX;
		}

		// �X�N���[�����W�ɕϊ�
		float screenPosX = strPosX / static_cast<float>(camera->GetScreenWidth() * 0.5f);
		float screenPoxY = strPosY / static_cast<float>(camera->GetScreenHeight() * 0.5f);

		// �e�N�X�`���p���b�V���ɏ���ݒ�
		mesh->SetTexture(currentFont.texture);
		mesh->SetPosition(tkl::Vector3(screenPosX, screenPoxY, 0.0f));
		mesh->SetScale(tkl::Vector3(currentFont.strWidth, currentFont.strHeight, 1.0f));
		mesh->Draw(camera);

		// ���̕����ʒu�v�Z�p
		prevPosX = strPosX;
		prevFont = currentFont;
	}
}

} // namespace tkl