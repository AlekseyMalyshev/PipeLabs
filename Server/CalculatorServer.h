#pragma once

#include <string>

#include "Communicator.h"
#include "ICalculator.h"
#include "IPipeCommunicator.h"

class CalculatorServer : public Communicator, public ICalculator, public IPipeCommunicator
{
public:
	CalculatorServer(HANDLE hPipe);

	virtual double Calculate(std::string formula);
	virtual std::string Echo(std::string string);

	virtual void Communicate();

};
