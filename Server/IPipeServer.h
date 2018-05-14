#pragma once

#include <string>

class IPipeServer
{
public:
	virtual void Listen() = 0;
	virtual void Shutdown() = 0;

};
