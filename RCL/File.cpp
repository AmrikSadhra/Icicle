#include "File.h"

using namespace RCL;

File::File(std::ifstream& ifstream)
{
	ASSERT(this->_SerializeIn(ifstream), "Failed to serialize File from file stream");
};

void File::_SerializeOut(std::ofstream& ofstream)
{
	ASSERT(false, "File output serialization is not currently implemented");
}

bool File::_SerializeIn(std::ifstream& ifstream)
{


	return true;
}
