#include "Communicator.h"

#include <iostream>

Communicator::Communicator(HANDLE hPipe) :
	_hPipe(hPipe)
{
}

template<class T>
bool Communicator::Send(T data)
{
	DWORD written;
	auto result = WriteFile(_hPipe, &data, sizeof(T), &written, 0);
	if (result != TRUE || written != sizeof(T))
	{
		std::cout << "Pipe server communication failed." << std::endl;
		_hPipe = INVALID_HANDLE_VALUE;
		return false;
	}
	return true;
}

template<class T>
bool Communicator::Receive(T* data)
{
	DWORD read;
	auto result = ReadFile(_hPipe, data, sizeof(T), &read, 0);
	if (result != TRUE || read != sizeof(T))
	{
		std::cout << "Pipe server communication failed." << std::endl;
		_hPipe = INVALID_HANDLE_VALUE;
		return false;
	}
	return true;
}

bool Communicator::Send(long data)
{
	return Send<long>(data);
}

bool Communicator::Send(double data)
{
	return Send<double>(data);
}

bool Communicator::Send(std::string data)
{
	DWORD data_length = (DWORD)data.length();
	if (!Send(data_length))
	{
		return false;
	}

	if (data_length > 0)
	{
		DWORD written;
		auto result = WriteFile(_hPipe, data.data(), data_length, &written, 0);
		if (result != TRUE || written != data.length())
		{
			std::cout << "Pipe server communication failed." << std::endl;
			_hPipe = INVALID_HANDLE_VALUE;
			return false;
		}
	}
	return true;
}

bool Communicator::Send(std::vector<byte> data)
{
	DWORD data_length = (DWORD)data.size() * sizeof(byte);
	if (!Send(data_length))
	{
		return false;
	}
	if (data_length > 0)
	{
		DWORD written;
		auto result = WriteFile(_hPipe, data.data(), data_length, &written, 0);
		if (result != TRUE || written != data_length)
		{
			std::cout << "Pipe server communication failed." << std::endl;
			_hPipe = INVALID_HANDLE_VALUE;
			return false;
		}
	}
	return true;
}

bool Communicator::Send(ISerializable* object)
{
	return Send(object->Serialize());
}

long Communicator::ReceiveLong()
{
	long result;
	Receive(&result);
	return result;
}

double Communicator::ReceiveDouble()
{
	double result;
	Receive(&result);
	return result;
}

std::string Communicator::ReceiveString()
{
	DWORD data_length;
	Receive(&data_length);
	std::string data(data_length, '\0');
	if (data_length > 0)
	{
		DWORD read;
		auto result = ReadFile(_hPipe, (void*)data.data(), data_length, &read, 0);
		if (result != TRUE || read != data_length)
		{
			std::cout << "Pipe server communication failed." << std::endl;
			_hPipe = INVALID_HANDLE_VALUE;
		}
	}
	return data;
}

std::vector<byte> Communicator::ReceiveBytes()
{
	DWORD data_length;
	Receive(&data_length);
	std::vector<byte> data(data_length, 0);
	if (data_length > 0)
	{
		DWORD read;
		auto result = ReadFile(_hPipe, data.data(), data_length, &read, 0);
		if (result != TRUE || read != data_length)
		{
			std::cout << "Pipe server communication failed." << std::endl;
			_hPipe = INVALID_HANDLE_VALUE;
		}
	}
	return data;
}

void Communicator::ReceiveSerializable(ISerializable* object)
{
	std::vector<byte> data = ReceiveBytes();
	object->Deserialize(data);
}
