#pragma once

#include <cstdio>
#include <cstdint>
#include <string>

namespace tkl
{
	wchar_t ToOnceWChara(const char* strSrc);
	void ToWChara(wchar_t* wstrDest, uint32_t destLegth, const std::string& src);
	void ToWChara(wchar_t* wstrDest, const char* strSrc, int length);
} // namespace tkl