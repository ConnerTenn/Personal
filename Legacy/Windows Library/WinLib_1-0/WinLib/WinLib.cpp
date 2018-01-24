
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
		pThis->WinLoad ? pThis->Render() :0;
		EndPaint(Hwnd, &pThis->Ps);
		return 0;
	case WM_ERASEBKGND:
		return (LRESULT)1;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(Hwnd, message, wParam, lParam);
	}
}

Window::Window(int width, int height, HINSTANCE hinstance, int iCmdShow)
{
	Width = width + 16;
	Height = height + 39;
	HInstance = hinstance;
	ICmdShow = iCmdShow;	
}

Window::~Window()
{
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
		Width,														// initial x size
		Height,														// initial y size
		NULL,														// parent window handle
		NULL,														// window menu handle
		HInstance,													// program instance handle
		this);														// creation parameters

	ShowWindow(Hwnd, ICmdShow);
	UpdateWindow(Hwnd);

	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	WinLoad = true;
}


Container *Window::CreateContainer(int x, int y, int width, int height)
{
	Container *container = new Container(x, y, width, height, NULL, this);
	ContainerList.push_back(container);
	return container;
}

void Window::UpdateMsg()
{
	PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE);

	InvalidateRect(Hwnd, NULL, true);

	TranslateMessage(&Msg);
	DispatchMessage(&Msg);
}

void Window::Render()
{
	HBRUSH HbrBkGnd;

	GetClientRect(Hwnd, &Rc);

	HdcMem = CreateCompatibleDC(Ps.hdc);

	HbmMem = CreateCompatibleBitmap(Ps.hdc, Rc.right - Rc.left,	Rc.bottom - Rc.top);

	HbmOld = (HBITMAP)SelectObject(HdcMem, HbmMem);

	HbrBkGnd = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(HdcMem, &Rc, HbrBkGnd);
	DeleteObject(HbrBkGnd);

	for (Container *container : ContainerList)
	{
		container->Render();
	}

	BitBlt(Ps.hdc, Rc.left, Rc.top,	Rc.right - Rc.left, Rc.bottom - Rc.top,	HdcMem,	0, 0, SRCCOPY);

	SelectObject(HdcMem, HbmOld);
	DeleteObject(HbmMem);
	DeleteObject(HbmOld);
	DeleteDC(HdcMem);

}





