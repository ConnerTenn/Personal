

class Surface;

#pragma once

#include "WinLib.h"
#undef DrawText

Int2 MeasureString(Surface *surface, std::string string, Font font);
Int2 MeasureString(Window *parentWindow, std::string string, Font font);

class Surface
{
public:
	Int2 Dimensions;
	Window *ParentWindow;
	Colour ClearColour;

	HBITMAP Hbm;//surface bitmap
	HDC Hdc;//surface
	//HFONT Hfnt;
	Gdiplus::Graphics *Graphics;
	//Gdiplus::Font *Typeface;

	Gdiplus::SolidBrush *SolidBrush;
	Gdiplus::Pen *Pen;
	Gdiplus::Font *Typeface;

	Surface(SurfaceInfo *surfaceInfo);
	~Surface();

	void Resize(Int2 dimensions);
	void Clear();
	void FillRectangle(int x, int y, int width, int height, Colour colour);
	void DrawRectangle(int x, int y, int width, int height, Colour colour, float size = 0.5);
	void FillEllipse(int x, int y, int width, int height, Colour colour);
	void FillEllipse(int x, int y, int width, int height, Colour colour, double startAngle, double sweepAngle);
	void DrawEllipse(int x, int y, int width, int height, Colour colour, float size = 0.5);
	void DrawEllipse(int x, int y, int width, int height, Colour colour, double startAngle, double sweepAngle, float size = 0.5);
	void DrawLine(int x1, int y1, int x2, int y2, Colour colour, float size = 0.5);
	void DrawImage(int x, int y, int width, int height, Texture *texture);
	void DrawText(int x, int y, std::string text, Font font);
	void CopySurface(Rect destRect, Surface *other, Rect otherRect);
};

