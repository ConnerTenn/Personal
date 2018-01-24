
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
		pThis->Input->MouseState.Click = true;
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
		return 0;
	case WM_MBUTTONUP:
		pThis->Input->MouseState.MPressed = false;
		return 0;
	default:
		return DefWindowProc(Hwnd, message, wParam, lParam);
	}
}

Window::Window(int width, int height, HINSTANCE hinstance, int iCmdShow)//:
	//Input(this)
{
	Width = width;
	Height = height;
	HInstance = hinstance;
	ICmdShow = iCmdShow;

	Input = new InputHandler(this);
}

Window::~Window()
{
	DeleteObject(Hbm);
	DeleteDC(Hdc);

	for (Container *container : ContainerList)
	{
		delete container;
	}
	Focus = 0;

	delete Input; Input = 0;

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

	Input->MouseState.DoubleClick = false;
	Input->MouseState.Click = false;

	PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE);

	InvalidateRect(Hwnd, NULL, true);

	TranslateMessage(&Msg);
	DispatchMessage(&Msg);

	Input->Update();


	//Message Code
	if (Input->MouseState.Click)
	{
		Focus = 0;
	}
	for (Container *container : ContainerList)
	{
		container->State.Focus = false;
		container->UpdateMsg();
	}
	if (Focus) { Focus->State.Focus = true; }
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





