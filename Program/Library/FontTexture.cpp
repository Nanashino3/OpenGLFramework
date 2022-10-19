#include "FontTexture.h"

#include <wrl.h>
#include <string>
#include "Utility.h"

void FontTexture::CreateFontTexture()
{
	// �f�o�b�O�p(��U�Œ�)
	int fontSize = 32;
	int fontWeight = 1000;
	std::string fontType = "";
	const wchar_t once = tkl::ToOnceWChara("��");

	// �t�H���g�̐���
	LOGFONTW logFont = {
		fontSize, 0, 0, 0,
		fontWeight, 0, 0, 0,
		SHIFTJIS_CHARSET,
		OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN,
		TEXT("")
	};

	std::string fontName = (fontType == "") ? "�l�r �o����" : fontType;
	wchar_t buff[256] = {0};
	tkl::ToWChara(buff, 256, fontName);

	memcpy(logFont.lfFaceName, buff, sizeof(logFont.lfFaceName));
	HFONT hFont = CreateFontIndirect(&logFont);

	// �t�H���g�r�b�g�}�b�v�擾
	const wchar_t* ch = &once;
	UINT code = static_cast<UINT>(*ch);

	// ���݂̃E�B���h�E�ɓK�p
	HDC hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	//*********************************************
	GLYPHMETRICS gm;
	CONST MAT2 mat = {{0, 1}, {0, 0}, {0, 0}, {0, 1}};
	DWORD size = GetGlyphOutlineW(hdc, code, GGO_GRAY4_BITMAP, &gm, 0, NULL, &mat);

	BYTE* pFontBMP = new BYTE[size];
	GetGlyphOutlineW(hdc, code, GGO_GRAY4_BITMAP, &gm, size, pFontBMP, &mat);

	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);

	int gmBlackBoxX = gm.gmBlackBoxX;
	int gmBlackBoxY = gm.gmBlackBoxY;
	int gmCellIncX = gm.gmCellIncX;
	int gmCellIncY = gm.gmCellIncY;
	POINT gmptGlyphOrigin = gm.gmptGlyphOrigin;

	int tmAscent = tm.tmAscent;
	int tmDescent = tm.tmDescent;
	int tmHeight = tm.tmHeight;
}