

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
	Gdiplus::GraphicsPath Path;

	Surface(SurfaceInfo *surfaceInfo);
	~Surface();

	Rect GetRect();
	void Resize(Int2 dimensions);
	void Clear();

	void FillRectangle(int x, int y, int width, int height, Colour colour);
	void FillRectangle(Int2 pos1, Int2 pos2, Colour colour);
	void FillRectangle(Rect rect, Colour colour);
	void FillRectangles(std::vector<Rect> rects, Colour colour);
	void DrawRectangle(int x, int y, int width, int height, Colour colour, float size = 0.5);
	void DrawRectangle(Int2 pos1, Int2 pos2, Colour colour, float size = 0.5);
	void DrawRectangle(Rect rect, Colour colour, float size = 0.5);
	void DrawRectangles(std::vector<Rect> rects, Colour colour, float size = 0.5);
	void FillEllipse(int x, int y, int width, int height, Colour colour);
	void FillEllipse(Int2 pos1, Int2 pos2, Colour colour);
	void FillEllipse(int x, int y, int width, int height, Colour colour, double startAngle, double sweepAngle);
	void FillEllipse(Int2 pos1, Int2 pos2, Colour colour, double startAngle, double sweepAngle);
	void DrawEllipse(int x, int y, int width, int height, Colour colour, float size = 0.5);
	void DrawEllipse(Int2 pos1, Int2 pos2, Colour colour, float size = 0.5);
	void DrawEllipse(int x, int y, int width, int height, Colour colour, double startAngle, double sweepAngle, float size = 0.5);
	void DrawEllipse(Int2 pos1, Int2 pos2, Colour colour, double startAngle, double sweepAngle, float size = 0.5);
	void DrawLine(int x1, int y1, int x2, int y2, Colour colour, float size = 0.5);
	void DrawLine(Int2 pos1, Int2 pos2, Colour colour, float size = 0.5);
	void DrawLines(std::vector<Int2> &points, Colour colour, float size = 0.5);
	void DrawPolygon(std::vector<Int2> &points, Colour colour, float size = 0.5);
	void DrawImage(int x, int y, int width, int height, Texture *texture);
	void DrawImage(Int2 pos1, Int2 pos2, Texture *texture);
	void DrawText(int x, int y, std::string text, Font font);
	void DrawText(Int2 pos, std::string text, Font font);
	void CopySurface(Rect destRect, Surface *other, Rect otherRect);

	void SetClip(Int2 pos1, Int2 pos2);
	void ResetClip();

	void DrawPath(std::vector<Int2> &points, Colour colour, float size = 0.5);
	void StartFigure();
	void ClearPath();
	void AddLine(Int2 pos1, Int2 pos2);
	void AddEllipse(Int2 pos, Int2 dimensions);
	void AddString(Int2 pos, std::string text, Font font);
	void DrawPath(Colour colour, float size = 0.5);
};



