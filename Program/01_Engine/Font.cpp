#include "Font.h"

#include "System.h"
#include "Mesh.h"
#include "FontManager.h"
#include "Camera/FixedCamera.h"
#include "../02_Library/Utility.h"

namespace tkl
{
std::shared_ptr<Camera> Font::sCamera = nullptr;
std::shared_ptr<Mesh> Font::sMesh = nullptr;

Font::Font()
{}

Font::~Font()
{}

// TODO�F�ꕔ�̕��������܂��\���ł��Ȃ���肠��(������)
void Font::DrawString(float posX, float posY, const std::string& str, std::shared_ptr<Camera> camera)
{
	if(!sMesh){ sMesh = Mesh::CreatePlaneForTexture(); }
	if(!camera){
		int screenWidth = 0, screenHeight = 0;
		tkl::System::GetInstance()->GetWindowSize(&screenWidth, &screenHeight);
		sCamera = std::make_shared<FixedCamera>(screenWidth, screenHeight);

		camera = sCamera;
	}

	camera->Update();

	wchar_t buff[256] = {0};
	tkl::ToWChara(buff, 256, str);

	float prevPosX = 0.0f;
	tkl::FontManager::Font prevFont = { nullptr, 0, 0 }, currentFont = { nullptr, 0, 0 };

	for(int i = 0; i < wcslen(buff); ++i){
		currentFont = tkl::FontManager::GetInstance()->GetFontTexture(buff[i]);
		float prevFontX = static_cast<float>(prevFont.strWidth * 0.5f);
		float currentFontX = static_cast<float>(currentFont.strWidth * 0.5f);

		// �V���������̈ʒu
		float strPosX = posX;
		float strPosY = posY;
		if(i > 0){ strPosX += prevPosX + prevFontX + currentFontX; }

		// �X�N���[�����W�ɕϊ�
		float screenPosX = strPosX / static_cast<float>(camera->GetScreenWidth() * 0.5f);
		float screenPoxY = strPosY / static_cast<float>(camera->GetScreenHeight() * 0.5f);

		// �e�N�X�`���p���b�V���ɏ���ݒ�
		sMesh->SetTexture(currentFont.texture);
		sMesh->SetPosition(tkl::Vector3(screenPosX, screenPoxY, 0.0f));
		sMesh->Draw(camera);

		// ���̕����ʒu�v�Z�p
		prevPosX = strPosX;
		prevFont = currentFont;
	}
}

} // namespace tkl