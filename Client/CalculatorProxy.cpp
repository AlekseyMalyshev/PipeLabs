#include "CalculatorProxy.h"

double CalculatorProxy::Calculate(std::string formula)
{
	Send(1l);

	Send(formula);
	return ReceiveDouble();
}

std::string CalculatorProxy::Echo(std::string string)
{
	Send(2l);

	Send(string);
	return ReceiveString();
}
