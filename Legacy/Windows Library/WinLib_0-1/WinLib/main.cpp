
#include "WinLib.h"
#include "Container.h"

Container *container1;
Container *container2;
Container *container3;

void Render()
{
	container1->DrawRect(0, 0, 299, 299);
	container1->DrawRect(10, 10, 289, 289);
	container1->DrawRect(20, 20, 279, 279);
	container2->DrawRect(00, 00, 299, 299);
}

void Render2()
{
	container3->DrawRect(10, 10, 289, 289);
}

INT WINAPI WinMain(HINSTANCE HInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	Window win(300, 300, HInstance, iCmdShow, "WinLib_0-1", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
	container1 = win.CreateContainer(-50, 0, 300, 300);
	container2 = container1->CreateContainer(100, 100, 300, 300);

	Window win2(300, 300, HInstance, iCmdShow, "WinLib_0-1", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
	container3 = win2.CreateContainer(0, 0, 300, 300);

	bool done = false;
	while (!done)
	{
		win.UpdateMsg();
		win2.UpdateMsg();

		if (win.Msg.message == WM_QUIT || win2.Msg.message == WM_QUIT)
		{
			done = true;
		}
	}
	delete container1; container1 = 0;
	delete container2; container2 = 0;
	delete container3; container3 = 0;
}

