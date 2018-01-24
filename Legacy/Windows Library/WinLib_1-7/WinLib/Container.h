
class Container;
#pragma once


#include "WinLib.h"
#include "WinLibTypes.h"
#include <windows.h>
#include <wingdi.h>
#include <vector>
#include <string>
#include <algorithm>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "winmm.lib")

class Container
{
private:
	std::vector<Container *> ContainerList;
	Container *Parent;
	Window *SrcWindow;
public:
	HDC *Hdc;
	HBITMAP *Hbm;
	HFONT Hfnt;
	Gdiplus::Graphics *Graphics;
	Gdiplus::SolidBrush *SolidBrush;
	Gdiplus::Pen *Pen;
	Gdiplus::Font *Typeface;
	HDC HdcDisplay;
	HBITMAP HbmDisplay;

public:
	int X, Y;
	int AbsX, AbsY;
	int Width, Height;
	double ScaleX = 1, ScaleY = 1;
	double AbsScaleX = 1, AbsScaleY = 1;
	bool Show = true;
	int FrameNum = 1;
	int CurrentFrame = 0;
	struct InternalState
	{
		bool Focus = false;
	} State;

public:
	Container(int x, int y, int width, int height, Container *parent, Window *srcWindow, int frameNum = 1);

	~Container();


	Container *CreateContainer(int x, int y, int width, int height, int frameNum = 1);
	void Remove();
	void Delete();

	void UpdateTransformations();

	void Render();

	void UpdateMsg();

public:
	void Translate(int x, int y);
	void SetPos(int x, int y);
	void Scale(double x, double y);
	void Resize(int width, int height);
	void SetCurrentFrame(int currentFrame);
	void SetShow(bool show);

public:
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
};



