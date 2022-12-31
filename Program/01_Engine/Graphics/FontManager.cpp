//****************************************************************************
// �t�@�C�����FFontManager(�t�H���g�Ǘ��҃N���X)
// ��@���@���F2022/10/27
#include "FontManager.h"
#include "Geometry/Texture.h"

#include "../../01_Engine/ResourceManager.h"
#include "../../02_Library/FontTexture.h"
#include "../../02_Library/Utility.h"

namespace tkl
{
FontManager* FontManager::sMyInstance = nullptr;
FontManager::FontManager()
{}

FontManager::~FontManager()
{}

FontManager* FontManager::GetInstance()
{
	if(!sMyInstance){ sMyInstance = new FontManager; }
	return sMyInstance;
}

void FontManager::DestroyInstance()
{
	TKL_SAFE_DELETE(sMyInstance);
}

//****************************************************************************
// �֐����FGetFontFromCreate
// �T�@�v�F�t�H���g�擾(���������t�H���g)
// ���@���Farg1 ���C�h����
// �߂�l�F�Ȃ�
// �ځ@�ׁF�����������C�u�����Ő�������������Ԃ�
//****************************************************************************
FontManager::Character FontManager::GetFontFromCreate(wchar_t once)
{
	auto iter = mCacheFonts.find(once);
	if(iter != mCacheFonts.end()){ return iter->second; }

	auto fontTex = tnl::CreateFontTexture(32, once);

	char* colorArray  = std::get<0>(fontTex).get();
	int textureWidth  = std::get<1>(fontTex);
	int textureHeight = std::get<2>(fontTex);
	int strWidth	  = std::get<3>(fontTex);
	int strHeight	  = std::get<4>(fontTex);

	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	texture->CreateBuffer(textureWidth, textureHeight, colorArray);

	Character ch = {texture, Vector3(strWidth, strHeight, 0)};
	mCacheFonts.emplace(once, ch);

	return ch;
}

//****************************************************************************
// �֐����FGetFontFromTTF
// �T�@�v�F�t�H���g�擾(TTF)
// ���@���Farg1 ���C�h����
// �߂�l�F�Ȃ�
// �ځ@�ׁFTTF�t�@�C������ǂݍ��񂾃t�H���g���擾
//****************************************************************************
FontManager::Character FontManager::GetFontFromTTF(unsigned char ch, int fontSize)
{
	auto font = tkl::ResourceManager::GetInstance()->GetFont(ch, fontSize);

	Character character = {
		std::get<0>(font), std::get<1>(font), std::get<2>(font)
	};
	return character;
}

} // namespace tkl