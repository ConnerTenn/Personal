
#ifndef _WINLIB_H
#define _WINLIB_H

#include <windows.h>
#include <string>
#include <vector>
#include <string>
#include <objidl.h>
#include <gdiplus.h>
#include "Container.h"
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "winmm.lib")


class Window
{
private:
	std::vector<Container *> ContainerList;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

	RECT Rc;
	HDC HdcMem;
	HBITMAP HbmMem, HbmOld;
	PAINTSTRUCT  Ps;

	Gdiplus::Graphics *Graphics;

	bool WinLoad = false;

private:
	void (*RenderFunc)();

public:
	HWND Hwnd;
	MSG Msg;
	WNDCLASS WndClass;
	HINSTANCE HInstance;
	int Width, Height;
	std::string Name;

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	Window(int width, int height, HINSTANCE hinstance, int iCmdShow, void(*render)(), std::string name, DWORD style);
	~Window();

	Container *CreateContainer(int x, int y, int width, int height);

	void UpdateMsg();

private:
	void Render();
};



#endif

