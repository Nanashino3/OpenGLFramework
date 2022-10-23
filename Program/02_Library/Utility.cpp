#include "Utility.h"

#include <wrl.h>

namespace tkl
{
wchar_t ToOnceWChara(const char* strSrc)
{
	wchar_t buff[2];
	ToWChara(buff, strSrc, 2);

	return buff[0];
}

void ToWChara(wchar_t* wstrDest, uint32_t destLength, const std::string& src)
{
	uint32_t size = static_cast<uint32_t>(src.size() + 1);
	char* buff = new char[size];

	memset(buff, 0, size);
	sprintf_s(buff, sizeof(char) * size, "%s", src.c_str());

	ToWChara(wstrDest, buff, destLength);
}

void ToWChara(wchar_t* wstrDest, const char* strSrc, int length)
{
	int result = MultiByteToWideChar(CP_ACP, 0, strSrc, -1, wstrDest, length);
	wstrDest[length - 1] = 0;
}

} // namespace tkl