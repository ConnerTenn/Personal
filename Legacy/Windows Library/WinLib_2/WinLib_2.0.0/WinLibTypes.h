
struct Int2;
struct Rect;
struct Colour;
struct Texture;
struct Font;

struct CallbackData;
struct MessageData;
struct TimerData;

struct WindowInfo;
struct SurfaceInfo;
struct TextArrayInfo;
struct ConsoleInfo;

#pragma once

#include <windows.h>
#include <windowsx.h>
#include <time.h>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "Msimg32.lib")

#define PI 3.14159265358979323
#define TAU (2.0 * PI)

#ifdef _DEBUG
#include <iostream>
#include <sstream>
#define DBOUT( s )            \
{                             \
   std::ostringstream os_;    \
   os_ << s;                   \
   OutputDebugString( os_.str().c_str() );  \
}
#endif

void Throw(std::string Message);



struct Int2
{
	int X = 0;
	int Y = 0;

	Int2();
	Int2(int x, int y);
	Int2(int pos[2]);
	Int2(Int2 &pos);

	int operator[](int i);
	Int2 operator+(Int2 other);
	Int2 operator-(Int2 other);
	Int2 operator*(Int2 other);
	Int2 operator/(Int2 other);
	Int2 operator+(int val);
	Int2 operator-(int val);
	Int2 operator*(int val);
	Int2 operator/(int val);
};

struct Rect
{
	Int2 Pos1;
	Int2 Pos2;

	Rect();
	Rect(int x1, int y1, int x2, int y2);
	Rect(int pos[4]);
	Rect(Int2 pos1, Int2 pos2);
	Rect(Rect &rect);
};

struct Colour
{
	BYTE R = 0, G = 0, B = 0, A = 255;
	Colour();
	Colour(BYTE r, BYTE g, BYTE b, BYTE a = 255);
};

struct Texture
{
	HBITMAP Hbm;
	int Width;
	int Height;

	Texture(std::string filename);
	~Texture();
};

#define WL_BOLD			0b0001
#define WL_ITALIC		0b0010
#define WL_UNDERLINE	0b0100
#define WL_STRIKEOUT	0b1000

struct Font
{
	std::string Typeface = "Consolas";
	int FontSize = 10;
	BYTE Style = 0;
	Colour FontColour = { 0, 0, 0, 255 };

	Font();
	Font(Colour fontColour);
	Font(std::string typeface);
	Font(std::string typeface, Colour fontColour);
	Font(std::string typeface, int fontSize, Colour fontColour, BYTE style = 0);
};

struct CallbackData
{
	UINT Message;
	WPARAM WParam;
	LPARAM LParam;
};

struct MessageData
{
	std::string Name;	
	std::vector<UINT64> Data;

	MessageData();
	MessageData(CallbackData message);

	bool operator==(UINT message);
	WPARAM WParam();
	LPARAM LParam();
};

struct TimerData
{
	int Id;
	int Delay;
	int Repeat;//0: no repeat   -1: indefinite Repeat  n: repeat for n times
};

//Info Structs

#include "WinLib.h"

struct WindowInfo
{
	std::string Name = "Window";
	Int2 Dimensions = { 0, 0 };
	Colour ClearColour = { 0, 0, 0, 255 };
	HINSTANCE HInstance;
	int ICmdShow;
	DWORD Style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX;
	void (*Callback)(Window *, MessageData);
};

struct SurfaceInfo
{
	Int2 Dimensions = { 100, 100 };
	Window *ParentWindow = 0;
	Colour ClearColour = { 0,0,0,255 };
};

struct TextArrayInfo
{
	Int2 Dimensions = { 100, 100 };
	bool Carry = true;
	Window *ParentWindow = 0;
	Font TextFont;
};

struct ConsoleInfo
{
	Int2 Dimensions = { 100, 100 };
	Window *ParentWindow = 0;
	Font TextFont;
};


