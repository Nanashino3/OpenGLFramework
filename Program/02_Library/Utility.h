//****************************************************************************
// �t�@�C�����FUtility
// ��@���@���F2022/10/21
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <cstdio>
#include <cstdint>
#include <string>
#include <vector>

namespace tkl
{
	#define TKL_SAFE_DELETE(p){ if(p){ delete p; p = nullptr ; }}
	
	// 1�����̃��C�h�����ϊ�
	wchar_t ToOnceWChara(const char* strSrc);
	// ���C�h�����ϊ�(������w��)
	void ToWChara(wchar_t* wstrDest, uint32_t destLegth, const std::string& src);
	// ���C�h�����ϊ�
	void ToWChara(wchar_t* wstrDest, const char* strSrc, int length);
	// CSV�̃��[�h
	std::vector<std::vector<std::string>> LoadCsv(const char* filename);
} // namespace tkl

#endif