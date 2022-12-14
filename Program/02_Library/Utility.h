#pragma once

#include <cstdio>
#include <cstdint>
#include <string>
#include <vector>

namespace tkl
{
	#define TKL_SAFE_DELETE(p){ if(p){ delete p; p = nullptr ; }}

	wchar_t ToOnceWChara(const char* strSrc);
	void ToWChara(wchar_t* wstrDest, uint32_t destLegth, const std::string& src);
	void ToWChara(wchar_t* wstrDest, const char* strSrc, int length);
	std::vector<std::vector<std::string>> LoadCsv(const char* filename);
} // namespace tkl