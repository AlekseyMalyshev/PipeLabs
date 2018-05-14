#pragma once

#include <string>
#include <vector>
#include <thread>

#include <windows.h>

#include "IPipeServer.h"
#include "Communicator.h"
#include "IPipeCommunicator.h"
#include "StringUtils.h"

template <class T>
class PipeServer : public IPipeServer
{
private:
	HANDLE _hPipe;
	std::string _address;
	std::unique_ptr<std::thread> _thread;

	bool OpenPipe();

public:
	PipeServer(const std::string& address);
	virtual void Listen();
	virtual void Shutdown();

	virtual ~PipeServer();

};

template<class T>
PipeServer<T>::PipeServer(const std::string& address) :
	_hPipe(INVALID_HANDLE_VALUE),
	_address(address)
{
}

template<class T>
void PipeServer<T>::Listen()
{
	while (OpenPipe())
	{
		if (ConnectNamedPipe(_hPipe, NULL) != FALSE)
		{
			auto handler = (IPipeCommunicator*)new T(_hPipe);
			new std::thread([this, handler]
			{
				handler->Communicate();
			});
		}
	}
}

template<class T>
bool PipeServer<T>::OpenPipe()
{
	const int buffer_size = 0;

	StringUtils str(_address);
	_hPipe = CreateNamedPipe(str.Convert(),
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		buffer_size,
		buffer_size,
		NMPWAIT_WAIT_FOREVER,
		NULL);

	const int erro_buf_size = 1024;
	char error_buf[erro_buf_size];

	if (_hPipe != INVALID_HANDLE_VALUE)
	{
		snprintf(error_buf, erro_buf_size, "Pipe server is listening on: \"%s\"", _address.c_str());
		std::cout << error_buf << std::endl;
		return true;
	}
	auto error = GetLastError();
	snprintf(error_buf, erro_buf_size, "Error while creating named pipe: 0x%.8d", error);
	std::cout << error_buf << std::endl;
	return false;
}

template<class T>
void PipeServer<T>::Shutdown()
{
	DisconnectNamedPipe(_hPipe);
	_hPipe = INVALID_HANDLE_VALUE;

	if (_thread != 0 && _thread->joinable())
	{
		_thread->join();
		_thread = 0;
	}
}

template<class T>
PipeServer<T>::~PipeServer()
{
	if (_hPipe != INVALID_HANDLE_VALUE && _thread != 0 && _thread->joinable())
	{
		Shutdown();
	}
}

