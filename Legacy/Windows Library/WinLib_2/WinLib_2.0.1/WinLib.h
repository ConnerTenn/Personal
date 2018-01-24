
class Window;

#pragma once

#include "WinLibTypes.h"
#include "Surface.h"
#include "InputHandler.h"
#include "Elements.h"

void ClockBegin();
void ClockEnd();

//add encapsulation
class Window
{
public:
	std::string Name;
	Int2 Dimensions;
	Colour ClearColour;

	int ICmdShow;
	WNDCLASS WndClass;
	HINSTANCE HInstance;
	DWORD Style;

	Gdiplus::GdiplusStartupInput GdiPlusStartupInput;
	ULONG_PTR GdiPlusToken;

	//std::vector<CallbackData> CallbackDataList;
	std::vector<MessageData> MessageList;
	void (*Callback)(Window *, MessageData, void *);
	void *CallbackPtr = 0;
	std::vector<TimerData> TimerList;

	HWND Hwnd;
	RECT Rc;
	//HBITMAP Hbm;//window surface bitmap
	//HDC Hdc;//window surface
	PAINTSTRUCT Ps;

	Surface *WindowSurface;

	clock_t PreviousTime = 0;

public:
	InputHandler *Input;

	struct InternalState
	{
		bool WinLoad = false;
		bool Quit = false;
		double Delta = 0;
		bool Focus;
	} State;

public:
	Window(WindowInfo *windowInfo);
	~Window();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);

	void Create();
	void PreMsg();
	static void GetMsg();
	void UpdateMsg();
	void AddMessage(MessageData message, bool singleInstance = false);//only allow one instance of the message to exist at a time (no repeats)
	void CreateTimer(int delay, int id, int repeat = 0);
	void Draw();

};
