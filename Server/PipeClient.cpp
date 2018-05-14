#include "PipeClient.h"

#include <iostream>

#include "StringUtils.h"

PipeClient::PipeClient() :
	Communicator(INVALID_HANDLE_VALUE)
{
}

bool PipeClient::Connect(std::string address)
{
	StringUtils str(address);
	_hPipe = CreateFile(
		str.Convert(),
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	const int erro_buf_size = 1024;
	char error_buf[erro_buf_size];
	if (_hPipe != INVALID_HANDLE_VALUE)
	{
		snprintf(error_buf, erro_buf_size, "Connected to server pipe: \"%s\"", address.c_str());
		std::cout << error_buf << std::endl;
		return true;
	}

	auto error = GetLastError();
	snprintf(error_buf, erro_buf_size, "Failed to connect to named pipe: 0x%.8d", error);
	std::cout << error_buf << std::endl;
	return false;
}

void PipeClient::Disconnect()
{
	if (_hPipe != INVALID_HANDLE_VALUE)
	{
		CloseHandle(_hPipe);
	}
}
