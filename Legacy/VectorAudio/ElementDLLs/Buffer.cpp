
#include "Buffer.h"

DllExport void *Init()
{
	return new BufferModule();
}

void BufferModule::DrawModule()
{

}

void BufferModule::Process()
{
	std::cout << "Process [" << Name.c_str() << "]:" << Position.X()  << " " << Position.Y() << "\n";

	int maxSize = 0;
	for (int i = 0; i < InputModules.size(); i++)
	{
		//for (int)
	}
}

