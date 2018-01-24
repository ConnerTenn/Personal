
#ifndef _CONTAINER_H
#define _CONTAINER_H

#include <windows.h>
#include <vector>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "winmm.lib")


class Container
{
private:
	std::vector<Container *> ContainerList;
	Container *Parent;

	Gdiplus::Graphics **GraphicsPtr;

public:
	int X, Y;
	int Width, Height;
	int ABSX, ABSY;

public:
	Container(int x, int y, int width, int height, Container *parent, Gdiplus::Graphics **graphicsPtr);

	~Container();


	Container *CreateContainer(int x, int y, int width, int height);

	void GetAbsPos();



public:
	void DrawRect(int x1, int y1, int x2, int y2);
};


#endif
