#include <Windows.h>
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	WNDCLASS wndclass;
	wndclass.lpszClassName = TEXT("A");
	RegisterClass(&wndclass);
	CreateWindow( TEXT("B"), TEXT("C"), 0, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
}