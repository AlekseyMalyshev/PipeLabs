# Named pipes sample

Sample solution that demonstrates named pipe interprocess communication on Windows

## Server

Once started server opens and waits for connection on a pipe named *"\\\\.\\pipe\\PipeLabs\\Calculator"*. Multiple clients are supported. For each client server creates a new communication object CalculatorServer.

## Client

When started, the client tries to connect to the pipe named *"\\\\.\\pipe\\PipeLabs\\Calculator"*. Currently there is no implementation. Calculator supports two functions:

*Echo* - send back whatever string is received

*Calculate* - accepts a formula to calculate, but does nothing, returns NaN

## Framework

**ICommunicator** - an interface that defines all functions that can be used to communicate across a pipe or, potentially another means of communication.

**Communicator** - implements the above interface.

Both classes are usied by client and server to send/receive on pipes

##

**ISerializable** - an interface that should be implemented by an object that can be send through the pipe. Currently does not have an implementation.

##

**IPipeServer** - a pipe server interface

**PipeServer** - implements the above interface. This is a template that uses an object as a template parameter

**IPipeCommunicator**  - an interface that shuold be implemented by a server side object to run communication on pipe.

##

**IPipeClient** - an interface that defines functions to connect to pipe server.

**PipeClient** - a class that supports the above interface.

##

**ICalculator** - sample interface that should be supported by an implementation of a calculator.

**CalculatorServer** - implements the above interface, but does nothing. Also uses *Communicator* to send/receive data and *IPipeCommunicator*, that is used by the server to start communication process with the object.

**CalculatorProxy**  - implements *ICalculator* interface, but sends the data to/from pipe server.