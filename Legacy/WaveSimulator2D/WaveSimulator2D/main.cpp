
#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <string>
using namespace std;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "winmm.lib")

#include "Engine.h"

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

	Graphics graphics(hdcMem);


	Pen pen(Color(255, 0, 255, 0));
	Gdiplus::SolidBrush brush(Color(255, 0, 255, 0));

	

	graphics.DrawRectangle(&pen, 100, 100, 65 + 10, 65 + 10);
	graphics.FillRectangle(&brush, 50 + 100, 50 + 100, 10, 10);

	graphics.DrawRectangle(&pen, 300, 100, 65 + 10, 65 + 10);
	graphics.FillRectangle(&brush, 50 + 300, 50 + 100, 10, 10);

	graphics.DrawRectangle(&pen, 105, 190, 65, 10);
	graphics.FillRectangle(&brush, 105, 190, 50, 10);
	graphics.DrawRectangle(&pen, 305, 190, 65, 10);
	graphics.FillRectangle(&brush, 305, 190, 50, 10);

	for (int i = 0; i < 11; i++)
	{
		graphics.DrawRectangle(&pen, 132, 210 + 10 * i, 10, 10);
	}
	for (int i = 0; i < 4; i++)
	{
		graphics.DrawRectangle(&pen, 332, 210 + 10 * i, 10, 10);
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

	string mystring = "Pos1: {" + to_string(56) + "," + to_string(456) + "}\n" + "Pos2: {" + to_string(34) + "," + to_string(5) + "}";

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

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Engine* engine = new Engine();

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{

	HWND                hWnd;
	//MSG                 msg;
	WNDCLASS            wndClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("Wave Simulator 2D");

	RegisterClass(&wndClass);

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

	hWnd = CreateWindowEx(WS_EX_APPWINDOW, TEXT("WIndowsGraphicsTest"), TEXT("WIndowsGraphicsTest"),
	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
	CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
	*/
	hWnd = CreateWindow(
		TEXT("Wave Simulator 2D"),
		TEXT("Wave Simulator 2D"),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800+16,
		600,
		NULL,
		NULL,
		hInstance,
		NULL);


	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	engine->Initilize(hWnd);
	engine->Loop();
	/*bool done = false;
	while (!done)
	{
		//GetMessage(&msg, NULL, 0, 0);
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		//HDC          hdc;
		//PAINTSTRUCT  ps;

		InvalidateRect(hWnd, NULL, true);
		//hdc = BeginPaint(hWnd, &ps);
		//OnPaint(hdc);
		//EndPaint(hWnd, &ps);
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		//if (msg.message == WM_PAINT)
		//{
		//	hdc = BeginPaint(hWnd, &ps);
		//	OnPaint(hdc);
		//	EndPaint(hWnd, &ps);
		//}
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
	}*/



	GdiplusShutdown(gdiplusToken);
	//return msg.wParam;
	return 0;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT  ps;

	switch (message)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		engine->OnPaint(hWnd, &ps);
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

