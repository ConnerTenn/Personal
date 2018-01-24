
#include "Include\VectorAudio.h"
#include "Include\Modules.h"

#ifdef _WIN32
#include <Windows.h>
#endif

void main()
{
	std::cout << "Version 0.1\n";
	std::cout << "Begin Generate Samples\n";
	const int size = 1 * 60 * 44100;
	float *data = new float[size];

	for (int i = 0; i < size; i++)
	{
		//data[i] = i % 80 < 40 ? 1.0 : -1.0; //square
		//data[i] = (float)(i % 80) / 40.0f - 1.0f; //sawtooth
		//data[i] = i % 80 < 40 ? float(i) / 20.0f - 1.0f : float(20 - i) / 20.0f - 1.0f; //triangle
		data[i] = (float)sin(double(i) / 80.0 * TAU); //sine
	}

	std::cout << "End Generate Samples\n";

	PortAudio audio;

	audio.Initialize();
	audio.Play(data, size);

	std::cout << "Begin Solve\n";
	bool valid;
	double intersection;
	for (long i = 0; i < 44100; i++)
	{
		Point<double> p1(0.5, 0.0);
		Point<double> p2(1.0, 0.0);
		Point<double> p3(1.0, 1.0);
		Point<double> p4(0.0, 2.0);
		intersection = GetIntersection(p1, p2, p3, p4, 0.4, valid);
	}

	if (valid) { std::cout << intersection << "\n"; }
	else { std::cout << "Invalid\n"; }

	std::cout << "End Solve\n";

	std::cout << "Begin DLL Test\n";

	typedef void *(*foo_t)();
	foo_t initModule = NULL;

	HMODULE hDLL = ::LoadLibrary(std::string("Buffer.dll").c_str());

	Pipeline pipeline;
	if (hDLL)
	{
		initModule = (foo_t)::GetProcAddress(hDLL, "Init");

		if (initModule)
		{
			ModuleBase *module1 = (ModuleBase *)initModule();
			ModuleBase *module2 = (ModuleBase *)initModule();
			*module1->Position.Yp() = 1;
			*module2->Position.Yp() = 2;
			//module->Process();
			pipeline.AddModule(module1);
			pipeline.AddModule(module2);
			pipeline.Process(module1);
			pipeline.RemoveModule(module1);
			pipeline.RemoveModule(module2);
			delete module1;
			delete module2;
		}
		else
		{
			std::cout << "Error Loading Functio:" << GetLastError() << "\n";
		}
	}
	else
	{
		std::cout << "Error Loading Library\n";
	}



	::FreeLibrary(hDLL);

	std::cout << "End DLL Test\n";


	std::string out = "Press Enter To Continue:"; std::cout << out;
	std::getline(std::cin, out);

	audio.Terminate();
	delete[] data; data = 0;
}
