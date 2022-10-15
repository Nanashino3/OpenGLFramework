#include "FontTexture.h"

#include <wrl.h>
#include <string>

void FontTexture::CreateFontTexture()
{
	// �f�o�b�O�p(��U�Œ�)
	int fontSize = 32;
	int fontWeight = 1000;
	std::string fontType = "";

	// �t�H���g�̐���
	LOGFONT logFont = {
		fontSize, 0, 0, 0,
		fontWeight, 0, 0, 0,
		SHIFTJIS_CHARSET,
		OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN,
		TEXT("")
	};

	std::string fintName = (fontType == "") ? "�l�r �o����" : fontType;
	HFONT hFont = CreateFontIndirect(&logFont);
}