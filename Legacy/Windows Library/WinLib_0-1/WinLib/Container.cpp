
#include "Container.h"

Container::Container(int x, int y, int width, int height, Container *parent, Window *srcWindow)
{
	X = x;
	Y = y;
	Width = width;
	Height = height;
	Parent = parent;
	SrcWindow = srcWindow;

	GetAbsPos();
}

Container::~Container()
{
	Parent = 0;

	//delete Graphics; Graphics = 0;
}

Container* Container::CreateContainer(int x, int y, int width, int height)
{
	Container* container = new Container(x, y, width, height, this, SrcWindow);
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

HDC* Container::GetHdc()
{
	return &Hdc;
}



void Container::DrawRect(int x1, int y1, int x2, int y2)
{
	Hdc = CreateCompatibleDC(SrcWindow->Ps.hdc);
	Hbm = CreateCompatibleBitmap(SrcWindow->Ps.hdc, Width, Height);
	SelectObject(Hdc, Hbm);
	Graphics = new Gdiplus::Graphics(Hdc);

	Gdiplus::Pen* Pen = new Gdiplus::Pen(Gdiplus::Color(255, 0, 255, 0));
	//(*GraphicsPtr)->DrawRectangle(Pen, x1 + ABSX, y1 + ABSY, x2-x1, y2-y1);
}