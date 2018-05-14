// main.cpp : Defines the entry point for the console application.
//

#include <memory>
#include <iostream>

#include "PipeServer.h"
#include "CalculatorServer.h"

int main(int argc, char *argv[])
{
	auto server = std::make_unique<PipeServer<CalculatorServer>>("\\\\.\\pipe\\PipeLabs\\Calculator");
	server->Listen();
	server->Shutdown();
	return 0;
}

