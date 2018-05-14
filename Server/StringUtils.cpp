#include "StringUtils.h"

#include <iostream>

StringUtils::StringUtils(std::string str) :
	_str(str)
{
}

LPCWSTR StringUtils::Convert()
{
	int slength = (int)_str.length() + 1;
	int len = MultiByteToWideChar(CP_ACP, 0, _str.c_str(), slength, 0, 0);
	_buffer = std::make_unique<wchar_t[]>(len);
	MultiByteToWideChar(CP_ACP, 0, _str.c_str(), slength, (LPWSTR)_buffer.get(), len);

	return (LPWSTR)_buffer.get();
}
