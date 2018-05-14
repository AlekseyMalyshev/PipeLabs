#pragma once

#include <string>

#include "IPipeClient.h"
#include "Communicator.h"

class PipeClient : public IPipeClient, public Communicator
{
public:
	PipeClient();

	virtual bool Connect(std::string address);
	virtual void Disconnect();

};
