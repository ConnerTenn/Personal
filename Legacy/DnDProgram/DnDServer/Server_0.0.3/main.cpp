﻿
#include "DnDProgram.h"



#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <fstream>
/*void RedirectIOToConsole()
{
	int hConHandle;
	intptr_t lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;

	// allocate a console for this app
	AllocConsole();

	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = 500;//MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

	// redirect unbuffered STDOUT to the console
	lStdHandle = (intptr_t)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);

	// redirect unbuffered STDIN to the console
	lStdHandle = (intptr_t)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "r");
	*stdin = *fp;
	setvbuf(stdin, NULL, _IONBF, 0);

	// redirect unbuffered STDERR to the console
	lStdHandle = (intptr_t)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stderr = *fp;
	setvbuf(stderr, NULL, _IONBF, 0);

	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
	// point to console as well
	std::ios::sync_with_stdio();

	freopen_s(&fp, "CONOUT$", "w", stdout);
}*/

DnD::DnDProgram *Program;

BOOL CtrlHandler(DWORD fdwCtrlType)
{
	if (CTRL_CLOSE_EVENT)
	{
		delete Program;
		return true;
	}
	else
	{
		return false;
	}
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{

	srand((unsigned int)time(NULL));
	//RedirectIOToConsole();
	//SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);

	Program = new DnD::DnDProgram(hInstance, iCmdShow);
	Program->Run();

	delete Program;
}


/*
------------
### TODO ###
------------

Grids
Save/Load
sub-editing
player handling
network

## Done ##
Memory Leaks
*/


