//****************************************************************************
// ファイル名：Utility
// 作　成　日：2022/10/21
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <cstdio>
#include <cstdint>
#include <string>
#include <vector>

namespace tkl
{
	#define TKL_SAFE_DELETE(p){ if(p){ delete p; p = nullptr ; }}
	
	// 1文字のワイド文字変換
	wchar_t ToOnceWChara(const char* strSrc);
	// ワイド文字変換(文字列指定)
	void ToWChara(wchar_t* wstrDest, uint32_t destLegth, const std::string& src);
	// ワイド文字変換
	void ToWChara(wchar_t* wstrDest, const char* strSrc, int length);
	// CSVのロード
	std::vector<std::vector<std::string>> LoadCsv(const char* filename);
} // namespace tkl

#endif