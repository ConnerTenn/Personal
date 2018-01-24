
class Window;
#pragma once


#include "Container.h"
#include "WinLibTypes.h"
#include <windows.h>
#include <windowsx.h>
#include <time.h>
#include <string>
#include <vector>
#include <string>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "winmm.lib")

class Window
{
private:
	std::vector<Container *> ContainerList;
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
	std::vector<Message> MessageList;
	bool KeyState[255][2];

	double Delta = 0;

	HDC Hdc;
	PAINTSTRUCT Ps;

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	Window(int width, int height, HINSTANCE hinstance, int iCmdShow);
	void Create();
	~Window();

	Container *CreateContainer(int x, int y, int width, int height);

	void UpdateMsg();

public:
	class InputHandler
	{
	private:
		Window *ParentWindow;
	public:
		Key KeyState[255];
		Mouse MouseState;
		InputHandler(Window *parentWindow);
		void Update();
	} Input;

public:
	void Render();
};




