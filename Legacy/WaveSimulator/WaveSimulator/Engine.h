
#pragma once

#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <string>
using namespace std;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "winmm.lib")

#include "Wave.h"

class Engine
{
private:
	HWND hWnd;
	bool Done = false;
	Wave wave;
public:
	void Initilize(HWND &hwnd);
	void OnPaint(HWND hWnd, LPPAINTSTRUCT lpPS);
	void Loop();
};