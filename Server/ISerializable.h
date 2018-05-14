#pragma once

#include <vector>

typedef unsigned char byte;

class ISerializable
{
public:
	virtual std::vector<byte> Serialize() = 0;
	virtual bool Deserialize(std::vector<byte>) = 0;

};
