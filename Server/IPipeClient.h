#pragma once

#include <string>

class IPipeClient
{
public:
	virtual bool Connect(std::string address) = 0;
	virtual void Disconnect() = 0;

};
