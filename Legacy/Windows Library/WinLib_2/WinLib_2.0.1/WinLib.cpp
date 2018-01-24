
#include "WinLib.h"

clock_t ClockTimer;

void ClockBegin()
{
	ClockTimer = clock();
}

void ClockEnd()
{
	ClockTimer = clock() - ClockTimer;
#if _DEBUG
	DBOUT("TIME: " << ClockTimer << "\n");
#endif
}


LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Window *pThis;
	if (message == WM_NCCREATE)
	{
		//pThis = static_cast<Window *>(reinterpret_cast<CREATESTRUCT *>(lParam)->lpCreateParams);
		pThis = (Window *)(((CREATESTRUCT *)lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis)))
		{
			if (GetLastError() != 0) { return FALSE; }
		}
	}
	else
	{
		pThis = reinterpret_cast<Window *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		//pThis->State.Create = true;
	}

	if (pThis)
	{
		//pThis->CallbackDataList.push_back({ message, wParam, lParam });
		pThis->MessageList.push_back(MessageData({ message, wParam, lParam }));
	}
	
	static int i = 0;
	switch (message)
	{
	//case WM_CREATE:
	//	return 0;
	case WM_PAINT:
		BeginPaint(hwnd, &pThis->Ps);
		//if (pThis->State.WinLoad) { BitBlt(pThis->Ps.hdc, pThis->Rc.left, pThis->Rc.top, pThis->Rc.right - pThis->Rc.left, pThis->Rc.bottom - pThis->Rc.top, pThis->WindowSurface->Hdc, 0, 0, SRCCOPY); }
		EndPaint(hwnd, &pThis->Ps);
		return (LRESULT)1;
	case WM_ERASEBKGND:
		return (LRESULT)1;
		
		/*case WM_DESTROY:
		pThis->State.Quit = true;
		return 0;
	case WM_KEYDOWN:
		pThis->Input->KeyState[wParam].Pressed = true;
		return 0;
	case WM_KEYUP:
		pThis->Input->KeyState[wParam].Pressed = false;
		return 0;
	case WM_LBUTTONDOWN:
		pThis->Input->MouseState.LPressed = true;
		pThis->Input->MouseState.LClick = true;
		if ((double)clock() - pThis->Input->MouseState.SecondPressCounter < pThis->Input->MouseState.DoubleClickDelay)
		{
			pThis->Input->MouseState.DoubleClick = true;
		}
		pThis->Input->MouseState.SecondPressCounter = (double)clock();
		return 0;
	case WM_LBUTTONUP:
		pThis->Input->MouseState.LPressed = false;
		return 0;
	case WM_RBUTTONDOWN:
		pThis->Input->MouseState.RPressed = true;
		pThis->Input->MouseState.RClick = true;
		return 0;
	case WM_RBUTTONUP:
		pThis->Input->MouseState.RPressed = false;
		return 0;
	case WM_MBUTTONDOWN:
		pThis->Input->MouseState.MPressed = true;
		return 0;
	case WM_MBUTTONUP:
		pThis->Input->MouseState.MPressed = false;
		return 0;*/
	default:
		DefWindowProc(hwnd, message, wParam, lParam);
		return (LRESULT)1;
	}
}

Window::Window(WindowInfo *windowInfo)
{
	Name = windowInfo->Name;
	Dimensions = windowInfo->Dimensions;
	ClearColour = windowInfo->ClearColour;
	HInstance = windowInfo->HInstance;
	ICmdShow = windowInfo->ICmdShow;
	Style = windowInfo->Style;
	Callback = windowInfo->Callback;
	CallbackPtr = windowInfo->CallbackPtr;

	Input = new InputHandler(this);
}

Window::~Window()
{
	//DeleteObject(Hbm);
	//DeleteDC(Hdc);
	delete WindowSurface; WindowSurface = 0;
	delete Input; Input = 0;

	for (int i = 0; i < TimerList.size(); i++)
	{
		KillTimer(Hwnd, TimerList[i].Id);
	}

	Gdiplus::GdiplusShutdown(GdiPlusToken);
}

void Window::Create()
{
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = HInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = TEXT(Name.c_str());

	RegisterClass(&WndClass);

	Hwnd = CreateWindow(
		TEXT(Name.c_str()),											// window class name
		TEXT(Name.c_str()),											// window caption
		Style,														// window style
		CW_USEDEFAULT,												// initial x position
		CW_USEDEFAULT,												// initial y position
		Dimensions.X + 16,											// initial x size
		Dimensions.Y + 39,											// initial y size
		NULL,														// parent window handle
		NULL,														// window menu handle
		HInstance,													// program instance handle
		this);														// creation parameters

	ShowWindow(Hwnd, ICmdShow);
	UpdateWindow(Hwnd);

	Gdiplus::GdiplusStartup(&GdiPlusToken, &GdiPlusStartupInput, NULL);

	GetClientRect(Hwnd, &Rc);

	SurfaceInfo surfaceInfo;
	surfaceInfo.Dimensions = { Rc.right - Rc.left, Rc.bottom - Rc.top };
	surfaceInfo.ClearColour = ClearColour;
	surfaceInfo.ParentWindow = this;
	WindowSurface = new Surface(&surfaceInfo);

	State.WinLoad = true;
	
	WindowSurface->Clear();
	InvalidateRect(Hwnd, NULL, true);
}

void Window::PreMsg()
{
	State.Delta = static_cast<double>(clock() - PreviousTime);
	if (PreviousTime == 0) { State.Delta = 0; }
	PreviousTime = clock();

	Input->MouseState.DoubleClick = false;
	Input->MouseState.LClick = false;
	Input->MouseState.RClick = false;
}

void Window::GetMsg()
{
	MSG msg;
	GetMessage(&msg, NULL, 0, 0);
	TranslateMessage(&msg);
	DispatchMessage(&msg);
}

void Window::UpdateMsg()
{
	//while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
	//{
	//	TranslateMessage(&msg);
	//	DispatchMessage(&msg);
	//}

	State.Focus = (GetFocus() == Hwnd);

	for (int i = 0; i < MessageList.size(); i++)
	{
		//events
		if (MessageList[i] == WM_CREATE)
		{
		}
		else if (MessageList[i] == WM_DESTROY)
		{
			State.Quit = true;
		}
		else if (MessageList[i] == WM_KEYDOWN)
		{
			Input->KeyState[MessageList[i].WParam()].Pressed = true;
		}
		else if (MessageList[i] == WM_KEYUP)
		{
			Input->KeyState[MessageList[i].WParam()].Pressed = false;
		}
		else if (MessageList[i] == WM_LBUTTONDOWN)
		{
			Input->MouseState.LPressed = true;
			Input->MouseState.LClick = true;
			if ((double)clock() - Input->MouseState.SecondPressCounter < Input->MouseState.DoubleClickDelay)
			{
				Input->MouseState.DoubleClick = true;
			}
			Input->MouseState.SecondPressCounter = (double)clock();
		}
		else if (MessageList[i] == WM_LBUTTONUP)
		{
			Input->MouseState.LPressed = false;
		}
		else if (MessageList[i] == WM_RBUTTONDOWN)
		{
			Input->MouseState.RPressed = true;
			Input->MouseState.RClick = true;
		}
		else if (MessageList[i] == WM_RBUTTONUP)
		{
			Input->MouseState.RPressed = false;
		}
		else if (MessageList[i] == WM_MBUTTONDOWN)
		{
			Input->MouseState.MPressed = true;
		}
		else if (MessageList[i] == WM_MBUTTONUP)
		{
			Input->MouseState.MPressed = false;
		}
		else if (MessageList[i] == WM_TIMER)
		{
			for (int j = 0; j < TimerList.size(); j++)
			{
				if (TimerList[j].Id == MessageList[i].WParam())
				{
					if (!TimerList[j].Repeat) { KillTimer(Hwnd, TimerList[j].Id); }
					else if (TimerList[j].Repeat > 0) { TimerList[j].Repeat--; }
					j = (int)TimerList.size();
				}
			}
		}
	}


	Input->Update();

	for (int i = 0; Callback && i < MessageList.size(); i++)
	{
		Callback(this, MessageList[i], CallbackPtr);
	}

	MessageList.clear();
}

void Window::AddMessage(MessageData message, bool singleInstance)
{
	if (!singleInstance)
	{
		PostMessage(Hwnd, message.Message, message.WParam(), message.LParam()); //MessageList.push_back(message);
	}
	else
	{
		bool add = true;
		for (int i = 0; i < MessageList.size(); i++)
		{
			if (message == MessageList[i])
			{
				add = false;
			}
		}
		if (add) { PostMessage(Hwnd, message.Message, message.WParam(), message.LParam()); }//MessageList.push_back(message); }
	}
}

void Window::CreateTimer(int delay, int id, int repeat)
{
	SetTimer(Hwnd, id, delay, (TIMERPROC)NULL);
	TimerList.push_back(TimerData{ id, delay, repeat });
}

void Window::Draw()
{
	//if (!DoDraw)
	//{
	//	DoDraw = true;
	//InvalidateRect(hwnd, NULL, true);
	//}
	//DBOUT("PAINT" << i++ << "\n");
	HDC hdc = GetDC(Hwnd);
	if (State.WinLoad) { BitBlt(hdc, Rc.left, Rc.top, Rc.right - Rc.left, Rc.bottom - Rc.top, WindowSurface->Hdc, 0, 0, SRCCOPY); }
	ReleaseDC(Hwnd, hdc);
}

