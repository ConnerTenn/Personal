
class Window;
#pragma once

#include "Container.h"
#include "InputHandler.h"
#include "WinLibTypes.h"
#include "Elements.h"
#include <windows.h>
#include <windowsx.h>
#include <time.h>
#include <string>
#include <vector>
#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "Msimg32.lib")

#ifdef _DEBUG
#include <iostream>
#include <sstream>
#define DBOUT( s )            \
{                             \
   std::ostringstream os_;    \
   os_ << s;                   \
   OutputDebugString( os_.str().c_str() );  \
}
#endif

class Window
{
private:
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

	RECT Rc;
	HBITMAP Hbm;

	clock_t PreviousTime = 0;

	bool WinLoad = false;

public:
	std::string Name = "Untitled";
	DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

	HWND Hwnd;
	MSG Msg;
	WNDCLASS WndClass;
	HINSTANCE HInstance;
	int ICmdShow;
	int Width, Height;

	std::vector<Container *> ContainerList;
	Container *Focus = 0;

	double Delta = 0;

	struct InternalState
	{
		//bool Create = false;
		bool Quit = false;
	} State;

	HDC Hdc;
	PAINTSTRUCT Ps;

private:
	std::queue<CallbackData> MessageQueue;
	std::mutex CallbackMutex;
	std::condition_variable CallbackConditionVariable;
	bool CallbackReady = false;
	std::thread CallbackThread;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static void WindowCallback(Window *win);

public:
	Window(int width, int height, HINSTANCE hinstance, int iCmdShow, void(*callback)(CallbackData message));
	void Create();
	~Window();

	Container *CreateContainer(int x, int y, int width, int height, int frameNum = 1);

	void (*Callback)(CallbackData message);
	void UpdateMsg();

public:
	InputHandler *Input;

public:
	void Render();
};




