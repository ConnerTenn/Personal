
class Container;
#pragma once


#include "WinLib.h"
#include <windows.h>
#include <vector>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "winmm.lib")


class Container
{
private:
	std::vector<Container*> ContainerList;
	Container *Parent;
	Window *SrcWindow;

	Gdiplus::Graphics *Graphics;
	HDC Hdc;
	HBITMAP Hbm;

public:
	int X, Y;
	int Width, Height;
	int ABSX, ABSY;

public:
	Container(int x, int y, int width, int height, Container* parent, Window* srcWindow);

	~Container();


	Container* CreateContainer(int x, int y, int width, int height);

	void GetAbsPos();
	HDC* Container::GetHdc();


public:
	void DrawRect(int x1, int y1, int x2, int y2);
};



