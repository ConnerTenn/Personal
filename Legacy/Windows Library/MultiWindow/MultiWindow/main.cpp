
//#include <stdafx.h>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <string>
using namespace std;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "winmm.lib")

DWORD xPos1, yPos1, xPos2, yPos2;
int zPos1, zPos2;
bool b1[11];
bool b2[11];

//use ASCII

static void OnPaint3(HWND hWnd, LPPAINTSTRUCT lpPS)
{
	RECT rc;
	HDC hdcMem;
	HBITMAP hbmMem, hbmOld;
	HBRUSH hbrBkGnd;
	HFONT hfntOld;
	HFONT hfnt = CreateFont(20, 10, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH, TEXT("OCR"));

	//
	// Get the size of the client rectangle.
	//

	GetClientRect(hWnd, &rc);

	//
	// Create a compatible DC.
	//

	hdcMem = CreateCompatibleDC(lpPS->hdc);

	//
	// Create a bitmap big enough for our client rectangle.
	//

	hbmMem = CreateCompatibleBitmap(lpPS->hdc,
		rc.right - rc.left,
		rc.bottom - rc.top);

	//
	// Select the bitmap into the off-screen DC.
	//

	hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);

	//
	// Erase the background.
	//

	hbrBkGnd = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(hdcMem, &rc, hbrBkGnd);
	DeleteObject(hbrBkGnd);

	Gdiplus::Graphics graphics(hdcMem);


	Pen pen(Color(255, 0, 255, 0));
	Gdiplus::SolidBrush brush(Color(255, 0, 255, 0));

	graphics.DrawRectangle(&pen, 100, 100, 65 + 10, 65 + 10);
	graphics.FillRectangle(&brush, xPos1 / 1000 + 100, yPos1 / 1000 + 100, 10, 10);

	graphics.DrawRectangle(&pen, 300, 100, 65 + 10, 65 + 10);
	graphics.FillRectangle(&brush, xPos2 / 1000 + 300, yPos2 / 1000 + 100, 10, 10);

	graphics.DrawRectangle(&pen, 105, 190, 65, 10);
	graphics.FillRectangle(&brush, 105, 190, zPos1 / 1000, 10);
	graphics.DrawRectangle(&pen, 305, 190, 65, 10);
	graphics.FillRectangle(&brush, 305, 190, zPos2 / 1000, 10);

	for (int i = 0; i < 11; i++)
	{
		graphics.DrawRectangle(&pen, 132, 210 + 10 * i, 10, 10);
		b1[i] ? graphics.FillRectangle(&brush, 132, 210 + 10 * i, 10, 10) : 0;
	}
	for (int i = 0; i < 4; i++)
	{
		graphics.DrawRectangle(&pen, 332, 210 + 10 * i, 10, 10);
		b2[i] ? graphics.FillRectangle(&brush, 332, 210 + 10 * i, 10, 10) : 0;
	}

	//
	// Select the font.
	//

	if (hfnt)
	{
		hfntOld = (HFONT)SelectObject(hdcMem, hfnt);
	}

	//
	// Render the image into the offscreen DC.
	//

	string mystring = "Pos1: {" + to_string(xPos1) + "," + to_string(yPos1) + "}\n" + "Pos2: {" + to_string(xPos2) + "," + to_string(yPos2) + "}";

	SetBkMode(hdcMem, TRANSPARENT);
	SetTextColor(hdcMem, RGB(0, 255, 0));
	DrawText(hdcMem, mystring.c_str(), -1, &rc, DT_LEFT);


	if (hfntOld)
	{
		SelectObject(hdcMem, hfntOld);
	}

	//
	// Blt the changes to the screen DC.
	//

	BitBlt(lpPS->hdc,
		rc.left, rc.top,
		rc.right - rc.left, rc.bottom - rc.top,
		hdcMem,
		0, 0,
		SRCCOPY);

	//
	// Done with off-screen bitmap and DC.
	//

	SelectObject(hdcMem, hbmOld);
	DeleteObject(hbmMem);
	DeleteObject(hbmOld);
	DeleteObject(hfnt);
	DeleteDC(hdcMem);

}

LRESULT CALLBACK WndProc1(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	HWND                hWnd1, hWnd2;
	MSG                 msg1, msg2;
	WNDCLASS            wndClass1, wndClass2;
	GdiplusStartupInput gdiplusStartupInput1, gdiplusStartupInput2;
	ULONG_PTR           gdiplusToken1, gdiplusToken2;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken1, &gdiplusStartupInput1, NULL);
	GdiplusStartup(&gdiplusToken2, &gdiplusStartupInput2, NULL);

	wndClass1.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass1.lpfnWndProc = WndProc1;
	wndClass1.cbClsExtra = 0;
	wndClass1.cbWndExtra = 0;
	wndClass1.hInstance = hInstance;
	wndClass1.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass1.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass1.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass1.lpszMenuName = NULL;
	wndClass1.lpszClassName = TEXT("WIndowsGraphicsTest1");

	RegisterClass(&wndClass1);

	wndClass2.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass2.lpfnWndProc = WndProc2;
	wndClass2.cbClsExtra = 0;
	wndClass2.cbWndExtra = 0;
	wndClass2.hInstance = hInstance;
	wndClass2.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass2.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass2.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass2.lpszMenuName = NULL;
	wndClass2.lpszClassName = TEXT("WIndowsGraphicsTest2");

	RegisterClass(&wndClass2);

	/*
	hWnd = CreateWindow(
	TEXT("GettingStarted"),   // window class name
	TEXT("Getting Started"),  // window caption
	WS_OVERLAPPEDWINDOW,      // window style
	CW_USEDEFAULT,            // initial x position
	CW_USEDEFAULT,            // initial y position
	CW_USEDEFAULT,            // initial x size
	CW_USEDEFAULT,            // initial y size
	NULL,                     // parent window handle
	NULL,                     // window menu handle
	hInstance,                // program instance handle
	NULL);                    // creation parameters
	*/

	hWnd1 = CreateWindow(
		TEXT("WIndowsGraphicsTest1"),								// window class name
		TEXT("WIndowsGraphicsTest1"),								// window caption
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,	// window style
		CW_USEDEFAULT,												// initial x position
		CW_USEDEFAULT,												// initial y position
		800,														// initial x size
		600,														// initial y size
		NULL,														// parent window handle
		NULL,														// window menu handle
		hInstance,													// program instance handle
		NULL);														// creation parameters

	hWnd2 = CreateWindow(
		TEXT("WIndowsGraphicsTest2"),								// window class name
		TEXT("WIndowsGraphicsTest2"),								// window caption
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,	// window style
		CW_USEDEFAULT,												// initial x position
		CW_USEDEFAULT,												// initial y position
		800,														// initial x size
		600,														// initial y size
		NULL,														// parent window handle
		NULL,														// window menu handle
		hInstance,													// program instance handle
		NULL);														// creation parameters


	ShowWindow(hWnd1, iCmdShow);
	UpdateWindow(hWnd1);

	ShowWindow(hWnd2, iCmdShow);
	UpdateWindow(hWnd2);

	PAINTSTRUCT  ps;

	bool done = false;
	while (!done)
	{
		PeekMessage(&msg1, NULL, 0, 0, PM_REMOVE);
		GetMessage(&msg2, NULL, 0, 0);

		if (msg1.message == WM_PAINT)
		{
			BeginPaint(hWnd1, &ps);
			OnPaint3(hWnd1, &ps);
			EndPaint(hWnd1, &ps);
		}

		InvalidateRect(hWnd1, NULL, true);
		InvalidateRect(hWnd2, NULL, true);

		TranslateMessage(&msg1);
		DispatchMessage(&msg1);
		TranslateMessage(&msg2);
		DispatchMessage(&msg2);

		if (msg1.message == WM_QUIT)
		{
			done = true;
		}
		if (msg2.message == WM_QUIT)
		{
			done = true;
		}
	}

	GdiplusShutdown(gdiplusToken1);
	GdiplusShutdown(gdiplusToken2);
	return msg1.wParam;
}  // WinMain

LRESULT CALLBACK WndProc1(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	//HDC          hdc;
	PAINTSTRUCT  ps;

	switch (message)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		OnPaint3(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_ERASEBKGND:
		return (LRESULT)1;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
} // WndProc


LRESULT CALLBACK WndProc2(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	//HDC          hdc;
	PAINTSTRUCT  ps;

	switch (message)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		//BeginPaint(hWnd, &ps);
		//OnPaint3(hWnd, &ps);
		//EndPaint(hWnd, &ps);
		return 0;
	case WM_ERASEBKGND:
		return (LRESULT)1;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
} // WndProc
