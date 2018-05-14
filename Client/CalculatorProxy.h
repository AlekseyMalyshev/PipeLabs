#pragma once

#include <string>

#include "ICalculator.h"
#include "PipeClient.h"

class CalculatorProxy : public ICalculator, public PipeClient
{
public:
	virtual double Calculate(std::string formula);
	virtual std::string Echo(std::string string);

};
