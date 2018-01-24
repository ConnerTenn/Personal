
#include "Container.h"

Container::Container(int x, int y, int width, int height, Container *parent, Window *srcWindow)
{
	X = x;
	Y = y;
	Width = width;
	Height = height;
	Parent = parent;
	SrcWindow = srcWindow;

	Hdc = CreateCompatibleDC(SrcWindow->Ps.hdc);
	Hbm = CreateCompatibleBitmap(SrcWindow->Ps.hdc, Width, Height);

	GetAbsPos();
}

Container::~Container()
{
	for (Container *container : ContainerList)
	{
		delete container;
	}

	Parent = 0;
	SrcWindow = 0;
	DeleteObject(Hdc);
	DeleteObject(Hbm);
	DeleteObject(Hfnt);
}

Container *Container::CreateContainer(int x, int y, int width, int height)
{
	Container *container = new Container(x, y, width, height, this, SrcWindow);
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


void Container::Render()
{
	BitBlt(SrcWindow->HdcMem, ABSX, ABSY, Width, Height, Hdc, 0, 0, SRCCOPY);
	for (Container *container : ContainerList)
	{
		container->Render();
	}
}


void Container::FillRectangle(int x, int y, int width, int height, Colour colour)
{
	SelectObject(Hdc, Hbm);
	Gdiplus::Graphics *Graphics = new Gdiplus::Graphics(Hdc);

	Gdiplus::SolidBrush *SolidBrush = new Gdiplus::SolidBrush(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B));
	Graphics->FillRectangle(SolidBrush, x, y, width, height);
	
	delete SolidBrush; SolidBrush = 0;
	delete Graphics; Graphics = 0;
}

void Container::DrawRectangle(int x, int y, int width, int height, Colour colour, float size)
{
	SelectObject(Hdc, Hbm);
	Gdiplus::Graphics *Graphics = new Gdiplus::Graphics(Hdc);

	Gdiplus::Pen *Pen = new Gdiplus::Pen(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B), size);
	Graphics->DrawRectangle(Pen, x, y, width, height);

	delete Pen; Pen = 0;
	delete Graphics; Graphics = 0;
}

void Container::FillEllipse(int x, int y, int width, int height, Colour colour)
{
	SelectObject(Hdc, Hbm);
	Gdiplus::Graphics *Graphics = new Gdiplus::Graphics(Hdc);

	Gdiplus::SolidBrush *SolidBrush = new Gdiplus::SolidBrush(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B));
	Graphics->FillEllipse(SolidBrush, x, y, width, height);

	delete SolidBrush; SolidBrush = 0;
	delete Graphics; Graphics = 0;
}

void Container::FillEllipse(int x, int y, int width, int height, Colour colour, double startAngle, double sweepAngle)
{
	SelectObject(Hdc, Hbm);
	Gdiplus::Graphics *Graphics = new Gdiplus::Graphics(Hdc);

	Gdiplus::SolidBrush *SolidBrush = new Gdiplus::SolidBrush(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B));
	Graphics->FillPie(SolidBrush, x, y, width, height, (startAngle / TAU * 360.0) - 90.0, (sweepAngle/TAU * 360.0));

	delete SolidBrush; SolidBrush = 0;
	delete Graphics; Graphics = 0;
}

void Container::DrawEllipse(int x, int y, int width, int height, Colour colour, float size)
{
	SelectObject(Hdc, Hbm);
	Gdiplus::Graphics *Graphics = new Gdiplus::Graphics(Hdc);

	Gdiplus::Pen *Pen = new Gdiplus::Pen(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B), size);
	Graphics->DrawEllipse(Pen, x, y, width, height);

	delete Pen; Pen = 0;
	delete Graphics; Graphics = 0;
}

void Container::DrawEllipse(int x, int y, int width, int height, Colour colour, double startAngle, double sweepAngle, float size)
{
	SelectObject(Hdc, Hbm);
	Gdiplus::Graphics *Graphics = new Gdiplus::Graphics(Hdc);

	Gdiplus::Pen *Pen = new Gdiplus::Pen(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B), size);
	Graphics->DrawArc(Pen, x, y, width, height, (startAngle / TAU * 360.0) - 90.0, (sweepAngle / TAU * 360.0));

	delete Pen; Pen = 0;
	delete Graphics; Graphics = 0;
}

void Container::DrawLine(int x1, int y1, int x2, int y2, Colour colour, float size)
{
	SelectObject(Hdc, Hbm);
	Gdiplus::Graphics *Graphics = new Gdiplus::Graphics(Hdc);

	Gdiplus::Pen *Pen = new Gdiplus::Pen(Gdiplus::Color(colour.A, colour.R, colour.G, colour.B), size);
	Graphics->DrawLine(Pen, x1, y1, x2, y2);

	delete Pen; Pen = 0;
	delete Graphics; Graphics = 0;
}

void Container::DrawText(int x, int y, std::string text, Font font)
{
	SelectObject(Hdc, Hbm);

	Hfnt = CreateFont(font.FontSize, font.FontSize / font.HeightWidthRatio, 0, 0, (font.Style & 0b0001) == 0b0001 ? FW_BOLD : FW_NORMAL, font.Style & 0b0010, font.Style & 0b0100, font.Style & 0b1000, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH, TEXT(font.Typeface.c_str()));
	SelectObject(Hdc, Hfnt);

	SetBkMode(Hdc, TRANSPARENT);
	SetTextColor(Hdc, RGB(0, 255, 0));
	
	//int width = text.size() * (font.FontSize / font.HeightWidthRatio);
	//int height = (std::count(text.begin(), text.end(), '\n') + 1) * font.FontSize;
	RECT rc = { x, y, (LONG)Width, (LONG)Height };
	DrawTextA(Hdc, text.c_str(), -1, &rc, DT_LEFT);

	DeleteObject(Hfnt);
}

