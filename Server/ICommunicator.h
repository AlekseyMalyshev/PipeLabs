#pragma once

#include <string>
#include <vector>

#include "ISerializable.h"

class ICommunicator
{
public:
	virtual bool Send(long data) = 0;
	virtual bool Send(double data) = 0;
	virtual bool Send(std::string data) = 0;
	virtual bool Send(std::vector<byte> data) = 0;
	virtual bool Send(ISerializable* object) = 0;

	virtual long ReceiveLong() = 0;
	virtual double ReceiveDouble() = 0;
	virtual std::string ReceiveString() = 0;
	virtual std::vector<byte> ReceiveBytes() = 0;
	virtual void ReceiveSerializable(ISerializable* object) = 0;

};
