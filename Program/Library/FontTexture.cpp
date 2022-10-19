#include "FontTexture.h"

#include <wrl.h>
#include <string>
#include "Utility.h"

void FontTexture::CreateFontTexture()
{
	// デバッグ用(一旦固定)
	int fontSize = 32;
	int fontWeight = 1000;
	std::string fontType = "";
	const wchar_t once = tkl::ToOnceWChara("あ");

	// フォントの生成
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

	std::string fontName = (fontType == "") ? "ＭＳ Ｐ明朝" : fontType;
	wchar_t buff[256] = {0};
	tkl::ToWChara(buff, 256, fontName);

	memcpy(logFont.lfFaceName, buff, sizeof(logFont.lfFaceName));
	HFONT hFont = CreateFontIndirect(&logFont);

	// フォントビットマップ取得
	const wchar_t* ch = &once;
	UINT code = static_cast<UINT>(*ch);

	// 現在のウィンドウに適用
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