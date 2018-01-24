
#include "Container.h"

Container::Container(int x, int y, int width, int height, Container *parent, Gdiplus::Graphics **graphicsPtr)
{
	X = x;
	Y = y;
	Width = width;
	Height = height;
	Parent = parent;

	GraphicsPtr = graphicsPtr;

	GetAbsPos();
}

Container::~Container()
{
	Parent = 0;

	//delete Graphics; Graphics = 0;
}

Container *Container::CreateContainer(int x, int y, int width, int height)
{
	Container *container = new Container(x, y, width, height, this, GraphicsPtr);
	ContainerList.push_back(container);
	return container;
}

void Container::GetAbsPos()
{
	ABSX = X;
	ABSY = Y;
	if (Parent)
	{
		Parent->GetAbsPos();
		ABSX += Parent->ABSX;
		ABSY += Parent->ABSY;
	}
}



void Container::DrawRect(int x1, int y1, int x2, int y2)
{
	Gdiplus::Pen *Pen = new Gdiplus::Pen(Gdiplus::Color(255, 0, 255, 0));
	(*GraphicsPtr)->DrawRectangle(Pen, x1 + ABSX, y1 + ABSY, x2-x1, y2-y1);
}