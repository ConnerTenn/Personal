
class Window;
#pragma once


#include "Container.h"
#include <windows.h>
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
	std::vector<Container*> ContainerList;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

	RECT Rc;
	HDC HdcMem;
	HBITMAP HbmMem, HbmOld;

	Gdiplus::Graphics* Graphics;

	bool WinLoad = false;

public:
	HWND Hwnd;
	MSG Msg;
	WNDCLASS WndClass;
	HINSTANCE HInstance;
	int Width, Height;
	std::string Name;


	PAINTSTRUCT  Ps;

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	Window(int width, int height, HINSTANCE hinstance, int iCmdShow, std::string name, DWORD style);
	~Window();

	Container *CreateContainer(int x, int y, int width, int height);

	void UpdateMsg();

private:
	void Render();
};




