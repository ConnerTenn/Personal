
class InputHandler;
#pragma once


#include "WinLibTypes.h"
#include "WinLib.h"
#include <windows.h>

struct Key
{
	bool Pressed = false;
	bool Hold = false;
	bool Press = false;

	double FlipDelay = 500;
	double FlipCounter = FlipDelay;
	bool Flip = false;
};

struct Mouse
{
	int X = 0, Y = 0;
	//int PrevX = 0, PrevY = 0;
	//int HoverX = 0, HoverY = 0;
	bool LPressed = false;
	bool RPressed = false;
	bool MPressed = false;
	//bool Hover = false;
	bool Click = false;
	bool DoubleClick = false;

	//double HoverDelay = 1000;
	//double HoverCounter = HoverDelay;

	bool FirstPressState = true;
	bool FirstReleaseState = false;
	bool SecondPressState = false;
	bool WaitReleaseState = false;
	double DoubleClickDelay = 500;
	double FirstReleaseCounter = 0;
	double SecondPressCounter = 0;
};


class InputHandler
{
private:
	Window *ParentWindow;
public:
	Key KeyState[255];
	Mouse MouseState;
	InputHandler(Window *parentWindow);
	void Update();
};

