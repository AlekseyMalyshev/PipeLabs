#pragma once

#include <string>
#include <memory>

#include "windows.h"

class StringUtils final
{
private:
	std::unique_ptr<wchar_t[]> _buffer;
	std::string _str;

public:
	StringUtils(std::string str);
	LPCWSTR Convert();

};
