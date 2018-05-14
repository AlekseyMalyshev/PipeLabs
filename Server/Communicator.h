#pragma once

#include <string>
#include <vector>

#include <windows.h>

#include "ICommunicator.h"

class Communicator : public ICommunicator
{
private:
	template<class T>
	bool Send(T data);
	template<class T>
	bool Receive(T* data);

protected:
	HANDLE _hPipe;

public:
	Communicator(HANDLE hPipe);

	virtual bool Send(long data);
	virtual bool Send(double data);
	virtual bool Send(std::string data);
	virtual bool Send(std::vector<byte> data);
	virtual bool Send(ISerializable* object);

	virtual long ReceiveLong();
	virtual double ReceiveDouble();
	virtual std::string ReceiveString();
	virtual std::vector<byte> ReceiveBytes();
	virtual void ReceiveSerializable(ISerializable* object);

};
