
#ifndef _BUFFER_
#define _BUFFER_

#include <iostream>
#include <Modules.h>

#define DllExport   __declspec( dllexport ) 

//DllExport void Foo(std::string str);

class BufferModule : public ModuleBase
{
public:
	void DrawModule();

	void Process();
};

extern "C"//not necessissary //fix spelling
{
	DllExport void *Init();
}

#endif

