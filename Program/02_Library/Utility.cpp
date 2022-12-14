//****************************************************************************
// ファイル名：Utility
// 作　成　日：2022/10/21
#include "Utility.h"

#include <wrl.h>
#include <fstream>
#include <sstream>

namespace tkl
{
// 1文字のワイド文字変換
wchar_t ToOnceWChara(const char* strSrc)
{
	wchar_t buff[2];
	ToWChara(buff, strSrc, 2);

	return buff[0];
}

// ワイド文字変換(文字列指定)
void ToWChara(wchar_t* wstrDest, uint32_t destLength, const std::string& src)
{
	uint32_t size = static_cast<uint32_t>(src.size() + 1);
	char* buff = new char[size];

	memset(buff, 0, size);
	sprintf_s(buff, sizeof(char) * size, "%s", src.c_str());

	ToWChara(wstrDest, buff, destLength);
}

// ワイド文字変換
void ToWChara(wchar_t* wstrDest, const char* strSrc, int length)
{
	int result = MultiByteToWideChar(CP_ACP, 0, strSrc, -1, wstrDest, length);
	wstrDest[length - 1] = 0;
}

// CSVのロード
std::vector<std::vector<std::string>> LoadCsv(const char* filename)
{
	std::vector<std::vector<std::string>> result;

	std::ifstream ifs(filename);

	std::string line;
	while(getline(ifs, line)){
		std::istringstream iss(line);

		std::string s;
		std::vector<std::string> datas;
		while(getline(iss, s, ',')){
			datas.emplace_back(s);
		}
		result.emplace_back(datas);
	}

	return result;
}

} // namespace tkl