
#include "WinLib.h"

LRESULT CALLBACK Window::WndProc(HWND Hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Window *pThis;
	if (message == WM_NCCREATE)
	{
		pThis = static_cast<Window *>(reinterpret_cast<CREATESTRUCT *>(lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis)))
		{
			if (GetLastError() != 0) { return FALSE; }
		}
	}
	else
	{
		pThis = reinterpret_cast<Window *>(GetWindowLongPtr(Hwnd, GWLP_USERDATA));
	}

	switch (message)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		BeginPaint(Hwnd, &pThis->Ps);
		if (pThis->WinLoad) { BitBlt(pThis->Ps.hdc, pThis->Rc.left, pThis->Rc.top, pThis->Rc.right - pThis->Rc.left, pThis->Rc.bottom - pThis->Rc.top, pThis->Hdc, 0, 0, SRCCOPY); }
		EndPaint(Hwnd, &pThis->Ps);
		return 0;
	case WM_ERASEBKGND:
		return (LRESULT)1;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		pThis->KeyState[wParam][0] = true;
		pThis->KeyState[wParam][1] = true;
		pThis->Input.KeyState[wParam].Pressed = true;
		return 0;
	case WM_KEYUP:
		pThis->KeyState[wParam][0] = false;
		pThis->Input.KeyState[wParam].Pressed = false;
		return 0;
	case WM_LBUTTONDOWN:
		pThis->Input.MouseState.LPressed = true;
		return 0;
	case WM_LBUTTONUP:
		pThis->Input.MouseState.LPressed = false;
		return 0;
	case WM_RBUTTONDOWN:
		pThis->Input.MouseState.RPressed = true;
		return 0;
	case WM_MBUTTONUP:
		pThis->Input.MouseState.MPressed = false;
		return 0;
	default:
		return DefWindowProc(Hwnd, message, wParam, lParam);
	}
}

Window::Window(int width, int height, HINSTANCE hinstance, int iCmdShow):
	Input(this)
{
	memset(KeyState, false, 255 * 2);
	Width = width;
	Height = height;
	HInstance = hinstance;
	ICmdShow = iCmdShow;
}

Window::~Window()
{
	DeleteObject(Hbm);
	DeleteDC(Hdc);

	for (Container *container : ContainerList)
	{
		delete container;
	}
	Gdiplus::GdiplusShutdown(gdiplusToken);
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
		style,														// window style
		CW_USEDEFAULT,												// initial x position
		CW_USEDEFAULT,												// initial y position
		Width + 16,													// initial x size
		Height + 39,												// initial y size
		NULL,														// parent window handle
		NULL,														// window menu handle
		HInstance,													// program instance handle
		this);														// creation parameters

	ShowWindow(Hwnd, ICmdShow);
	UpdateWindow(Hwnd);

	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	GetClientRect(Hwnd, &Rc);
	Hdc = CreateCompatibleDC(Ps.hdc);
	Hbm = CreateCompatibleBitmap(Ps.hdc, Rc.right - Rc.left, Rc.bottom - Rc.top);
	SelectObject(Hdc, Hbm);

	WinLoad = true;
}


Container *Window::CreateContainer(int x, int y, int width, int height)
{
	Container *container = new Container(x, y, width, height, NULL, this);
	ContainerList.push_back(container);
	return container;
}

//###

void Window::UpdateMsg()
{
	Delta = static_cast<double>(clock() - PreviousTime);
	if (PreviousTime == 0) { Delta = 0; }
	PreviousTime = clock();
	
	for (int i = 0; i < 255; KeyState[i][1] = false, i++);

	TRACKMOUSEEVENT a;
	a.cbSize = sizeof(TRACKMOUSEEVENT);
	a.dwFlags = 1;
	a.hwndTrack = Hwnd;
	TrackMouseEvent(&a);

	PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE);

	InvalidateRect(Hwnd, NULL, true);

	TranslateMessage(&Msg);
	DispatchMessage(&Msg);

	Input.Update();


	//Message Code

	for (Container *container : ContainerList)
	{
		container->UpdateMsg();
	}
}

//###

Window::InputHandler::InputHandler(Window *parentWindow)
{
	ParentWindow = parentWindow;
}

void Window::InputHandler::Update()
{
	//Keys
	for (int i = 0; i < 255; i++)
	{
		Key *key = &KeyState[i];
		if (key->Pressed) 
		{
			if (key->FlipCounter <= 0)
			{
				key->Flip = !key->Flip;
			}
			else
			{
				key->FlipCounter -= ParentWindow->Delta;
			}
			if (key->Hold)
			{
				key->Press = false;
			}
			else
			{
				key->Press = true;
				key->Hold = true;
			}
		}
		else
		{
			key->Hold = false;
			key->Press = false;
			key->FlipCounter = key->FlipDelay;
			key->Flip = false;
		}
	}

	//Mouse
	Mouse *mouse = &MouseState;
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(ParentWindow->Hwnd, &point);
	mouse->X = point.x; mouse->Y = point.y;
	if (mouse->X < 0 || mouse->X > ParentWindow->Width) { mouse->X = -1; mouse->Y = -1; }
	if (mouse->Y < 0 || mouse->Y > ParentWindow->Height) { mouse->X = -1; mouse->Y = -1; }
	if (GetFocus() != ParentWindow->Hwnd) { mouse->X = -1; mouse->Y = -1; }
	if (mouse->X != -1)
	{
		
	}
	if (mouse->DoubleClick)
	{
		mouse->DoubleClick = false;
	}
	if (!mouse->FirstDownState)
	{
		if (mouse->LPressed)
		{
			mouse->FirstDownCounter += ParentWindow->Delta;
		}
		else
		{
			if (mouse->FirstDownCounter < mouse->DoubleClickDelay && mouse->FirstDownCounter)
			{
				mouse->FirstDownState = true;
			}
			else
			{
				mouse->FirstDownState = false;
				//mouse->SecondDownState = false;
				//mouse->SecondUpState = false;
			}
			mouse->FirstDownCounter = 0;
		}
	}
	else //if (!mouse->FirstUpState)
	{
		if (!mouse->LPressed)
		{
			mouse->FirstUpCounter += ParentWindow->Delta;
		}
		else
		{
			if (mouse->FirstUpCounter < mouse->DoubleClickDelay && mouse->FirstUpCounter)
			{
				mouse->DoubleClick = true;
				//mouse->FirstUpState = true;
			}
			else
			{
				//mouse->FirstDownState = false;
				//mouse->SecondDownState = false;
				//mouse->SecondUpState = false;
			}
			mouse->FirstUpCounter = 0;
		}
	}
	/*else if (!mouse->SecondDownState)
	{
		if (mouse->LPressed)
		{
			mouse->SecondDownCounter += ParentWindow->Delta;
		}
		else
		{
			if (mouse->SecondDownCounter < mouse->DoubleClickDelay && mouse->SecondDownCounter)
			{
				mouse->SecondDownState = true;
				//mouse->DoubleClick = true;
			}
			else
			{
				//mouse->FirstDownState = false;
				mouse->SecondDownState = false;
				//mouse->SecondUpState = false;
			}
			mouse->SecondDownCounter = 0;
		}
	}
	else if (!mouse->SecondUpState)
	{
		//mouse->SecondUpCounter += ParentWindow->Delta;
	}*/
}

//###

void Window::Render()
{
	HBRUSH HbrBkGnd;

	HbrBkGnd = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(Hdc, &Rc, HbrBkGnd);
	DeleteObject(HbrBkGnd);

	for (Container *container : ContainerList)
	{
		container->Render();
	}
}





