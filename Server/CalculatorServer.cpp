#include "CalculatorServer.h"

#include <iostream>

CalculatorServer::CalculatorServer(HANDLE hPipe) :
	Communicator(hPipe)
{
}

double CalculatorServer::Calculate(std::string formula)
{
	return std::numeric_limits<double>::quiet_NaN();
}

std::string CalculatorServer::Echo(std::string string)
{
	return string;
}

void CalculatorServer::Communicate()
{
	while (_hPipe != INVALID_HANDLE_VALUE)
	{
		long function = ReceiveLong();
		if (_hPipe == INVALID_HANDLE_VALUE)
		{
			break;
		}
		else if (function == 1)
		{
			auto formula = ReceiveString();
			auto result = Calculate(formula);
			Send(result);
		}
		else if (function == 2)
		{
			auto string = ReceiveString();
			string = Echo(string);
			Send(string);
		}
		else
		{
			std::cout << "Error, invalid function called: " << function << std::endl;
		}
	}
	delete this;
}
