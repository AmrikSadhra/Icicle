#pragma once

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

#include "../../../Utils.h"

class IRawData
{
protected:
	virtual bool _SerializeIn(std::ifstream& ifstream) = 0;
	virtual void _SerializeOut(std::ofstream& ofstream) = 0;
};
