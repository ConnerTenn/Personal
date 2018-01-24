
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
#include <algorithm>
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
	Int2(const Int2 &pos);

	int operator[](int i);
	Int2 operator+(Int2 other);
	Int2 operator-(Int2 other);
	Int2 operator*(Int2 other);
	Int2 operator/(Int2 other);
	Int2 operator+(int val);
	Int2 operator-(int val);
	Int2 operator*(int val);
	Int2 operator/(int val);
	bool operator==(Int2 other);
};

struct Rect
{
	Int2 Pos1;
	Int2 Pos2;

	Rect();
	Rect(int x1, int y1, int x2, int y2);
	Rect(int pos[4]);
	Rect(Int2 pos1, Int2 pos2);
	Rect(const Rect &rect);

	bool Intersect(Int2 point);
	bool Intersect(Rect other);

	Rect operator+(Int2 pos);
	Rect operator-(Int2 pos);
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
	float FontSize = 10;
	BYTE Style = 0;
	Colour FontColour = { 0, 0, 0, 255 };

	Font();
	Font(Colour fontColour);
	Font(std::string typeface);
	Font(std::string typeface, Colour fontColour);
	Font(std::string typeface, float fontSize, Colour fontColour, BYTE style = 0);
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
	UINT Message;
	std::vector<UINT64> Data;

	MessageData();
	MessageData(CallbackData message);

	bool operator==(UINT message);
	bool operator==(MessageData message);
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
	void (*Callback)(Window *, MessageData, void *) = 0;
	void *CallbackPtr = 0;
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


#define WL_0 0x30
#define WL_1 0x31
#define WL_2 0x32
#define WL_3 0x33
#define WL_4 0x34
#define WL_5 0x35
#define WL_6 0x36
#define WL_7 0x37
#define WL_8 0x38
#define WL_9 0x39

#define WL_A 0x41
#define WL_B 0x42
#define WL_C 0x43
#define WL_D 0x44
#define WL_E 0x45
#define WL_F 0x46
#define WL_G 0x47
#define WL_H 0x48
#define WL_I 0x49
#define WL_J 0x4A
#define WL_K 0x4B
#define WL_L 0x4C
#define WL_M 0x4D
#define WL_N 0x4E
#define WL_O 0x4F
#define WL_P 0x50
#define WL_Q 0x51
#define WL_R 0x52
#define WL_S 0x53
#define WL_T 0x54
#define WL_U 0x55
#define WL_V 0x56
#define WL_W 0x57
#define WL_X 0x58
#define WL_Y 0x59
#define WL_Z 0x5A

#define WL_SHIFT VK_SHIFT
#define WL_RETURN VK_RETURN
#define WL_BACKSPACE VK_BACK
#define WL_TAB VK_TAB
#define WL_UP VK_UP
#define WL_DOWN VK_DOWN
#define WL_LEFT VK_LEFT
#define WL_RIGHT VK_RIGHT

#define WL_UPDATESURFACE 0x1000
