// main.cpp : Defines the entry point for the console application.
//

#include <memory>
#include <iostream>

#include "CalculatorProxy.h"

int main(int argc, char *argv[])
{
	auto calc = std::make_unique<CalculatorProxy>();
	calc->Connect("\\\\.\\pipe\\PipeLabs\\Calculator");
	std::string line;
	std::cout << "<< ";
	while (getline(std::cin, line))
	{
		std::cout << ">> Echo: " << calc->Echo(line) << std::endl;
		std::cout << ">> Calculate: " << calc->Calculate(line) << std::endl;
		std::cout << "<< ";
	}
	calc->Disconnect();
	return 0;
}
