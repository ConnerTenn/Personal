
#include "Engine.h"

void Engine::Initilize(HWND &hwnd)
{
	hWnd = hwnd;
}

void Engine::OnPaint(HWND hWnd, LPPAINTSTRUCT lpPS)
{
	RECT rc;
	HDC hdcMem;
	HBITMAP hbmMem, hbmOld;
	HBRUSH hbrBkGnd;
	HFONT hfntOld;
	HFONT hfnt = CreateFont(20, 10, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH, TEXT("OCR"));

	// Get the size of the client rectangle.
	GetClientRect(hWnd, &rc);

	// Create a compatible DC.
	hdcMem = CreateCompatibleDC(lpPS->hdc);

	// Create a bitmap big enough for our client rectangle.
	hbmMem = CreateCompatibleBitmap(lpPS->hdc,
		rc.right - rc.left,
		rc.bottom - rc.top);

	// Select the bitmap into the off-screen DC.
	hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);

	// Erase the background.
	hbrBkGnd = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(hdcMem, &rc, hbrBkGnd);
	DeleteObject(hbrBkGnd);

	Graphics graphics(hdcMem);

	Pen pen(Color(255, 0, 255, 0));
	Gdiplus::SolidBrush brush(Color(255, 0, 255, 0));

	hfntOld = (HFONT)SelectObject(hdcMem, hfnt);

	string mystring;

	SetBkMode(hdcMem, TRANSPARENT);
	SetTextColor(hdcMem, RGB(0, 255, 0));

	// == Begin Draw ==

	/*
	for (int x = 0; x < NumPoints; x+=1)
	{
		brush.SetColor(Color(255, 0, 0, 255));
		brush.SetColor(Color(355/4, 0, 0, 255));
		graphics.FillRectangle(&brush, x, int(-wave.WaveData[x][0] + 300 - int(wave.WaveData[x][1] * 50)), 1, int(wave.WaveData[x][1]*50));
		brush.SetColor(Color(355 / 4, 255, 0, 0));
		graphics.FillRectangle(&brush, x, int(-wave.WaveData[x][0] + 300), 1, -int(wave.WaveData[x][1]*50));
		brush.SetColor(Color(255, 0, 255, 0));

		brush.SetColor(Color(355 / 4, 0, 0, 255));
		graphics.FillRectangle(&brush, x, int(300-int(wave.WaveData[x][1] * 50)), 1, int(wave.WaveData[x][1] * 50));
		brush.SetColor(Color(355 / 4, 255, 0, 0));
		graphics.FillRectangle(&brush, x, 300, 1, -int(wave.WaveData[x][1] * 50));
		brush.SetColor(Color(255, 0, 255, 0));

		graphics.FillRectangle(&brush, x, -int(wave.WaveData[x][0])+300, 1, 1);
	}
*/

	for (int x = 0; x < Dimensions; x += 1)
	{
		for (int y = 0; y < Dimensions; y += 1)
		{
			//brush.SetColor(Color(255, 0, 0, wave.WaveData[x][y][0]));
			int red = -int(wave.WaveData[x][y][0] < 0 ? wave.WaveData[x][y][0] : 0) / 100;
			int blue = int(wave.WaveData[x][y][0] > 0 ? wave.WaveData[x][y][0] : 0) / 100;
			brush.SetColor(Color(255, red, 0, blue));
			graphics.FillRectangle(&brush, x, y, 1, 1);
		}
	}

	// == End Draw ==

	SelectObject(hdcMem, hfntOld);

	// Blt the changes to the screen DC.
	BitBlt(lpPS->hdc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, hdcMem, 0, 0, SRCCOPY);

	// Done with off-screen bitmap and DC.
	SelectObject(hdcMem, hbmOld);
	DeleteObject(hbmMem);
	DeleteObject(hbmOld);
	DeleteObject(hfnt);
	DeleteDC(hdcMem);
}

void Engine::Loop()
{
	MSG msg;

	wave.Initilize();

	while (!Done)
	{
		static int count = 0;
		//count > 30? wave.Update(), count = 0: count++;
		wave.Update();

		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		InvalidateRect(hWnd, NULL, true);

		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
		{
			Done = true;
		}
	}
}


