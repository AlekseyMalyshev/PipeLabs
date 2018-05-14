#pragma once

#include <string>

class ICalculator
{
public:
	virtual double Calculate(std::string formula) = 0;
	virtual std::string Echo(std::string string) = 0;

};
