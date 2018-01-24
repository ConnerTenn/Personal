
#include "WinLib.h"

TextArray *textArray;
Console *console;

void DrawInputs(Window *window)
{
	window->WindowSurface->Clear();
	for (int i = 0; i < 255; i++)
	{
		if (window->Input->KeyState[i].Pressed)
		{
			window->WindowSurface->FillRectangle(10 * (i % 50) + 5, 10 * int(i / 50) + 10, 10, 10, { 50, 200, 50, 255 });
		}
		else
		{
			window->WindowSurface->DrawRectangle(10 * (i % 50) + 5, 10 * int(i / 50) + 10, 10, 10, { 50, 200, 50, 255 });
		}
	}
	if (window->Input->MouseState.LPressed) { window->WindowSurface->FillRectangle(5, 90, 10, 10, { 50, 200, 50, 255 }); }
	else { window->WindowSurface->DrawRectangle(5, 90, 10, 10, { 50, 200, 50, 255 }); }
	if (window->Input->MouseState.RPressed) { window->WindowSurface->FillRectangle(15, 90, 10, 10, { 50, 200, 50, 255 }); }
	else { window->WindowSurface->DrawRectangle(15, 90, 10, 10, { 50, 200, 50, 255 }); }
	if (window->Input->MouseState.MPressed) { window->WindowSurface->FillRectangle(25, 90, 10, 10, { 50, 200, 50, 255 }); }
	else { window->WindowSurface->DrawRectangle(25, 90, 10, 10, { 50, 200, 50, 255 }); }

	window->WindowSurface->DrawText(400, 200, "Test string\nTest", Font("Consolas", 20, Colour(0, 255, 50)));

	textArray->Draw();
	window->WindowSurface->CopySurface({ {900/2,000}, { textArray->TextSurface->Dimensions.X + 900/2, textArray->TextSurface->Dimensions.Y + 000 } }, textArray->TextSurface, { {0,0}, { textArray->TextSurface->Dimensions.X, textArray->TextSurface->Dimensions.Y} });
	//textArray->Resize({ textArray->Dimensions.X + 1, textArray->Dimensions.Y });

	static int i = 0;
	console->Text.push_back(std::string("Test") + std::to_string(i++));
	console->Draw();
	window->WindowSurface->CopySurface({ { 0,000 },{ console->TextSurface->Dimensions.X, console->TextSurface->Dimensions.Y + 000 } }, console->TextSurface, { { 0,0 },{ console->TextSurface->Dimensions.X, console->TextSurface->Dimensions.Y } });

	window->Draw();
}

void Callback(Window *window, MessageData Message)
{
	//static int i = 0;
	if (Message == WM_CREATE || Message == WM_KEYDOWN || Message == WM_KEYUP || Message == WM_LBUTTONDOWN || Message == WM_LBUTTONUP || Message == WM_RBUTTONDOWN || Message == WM_RBUTTONUP || Message == WM_MBUTTONDOWN || Message == WM_MBUTTONUP)
	{
		DrawInputs(window);
	}
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	WindowInfo windowInfo;
	windowInfo.Dimensions = { 900, 600 };
	windowInfo.ClearColour = { 20, 20, 50, 255 };
	windowInfo.HInstance = hInstance;
	windowInfo.ICmdShow = iCmdShow;
	windowInfo.Style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	windowInfo.Callback = Callback;
	Window window(&windowInfo);

	window.Create();

	TextArrayInfo textArrayInfo;
	textArrayInfo.Dimensions = { 61,39 };
	textArrayInfo.ParentWindow = &window;
	textArrayInfo.TextFont = Font("Consolas", 10, Colour(0, 55, 200));
	textArray = new TextArray(&textArrayInfo);

	std::string stringI = "Hello, My name is Charlie!", string; for (int i = 0; i < 10000; i++, string = string + stringI) {}
	textArray->WriteString({ 0,0 }, string);

	ConsoleInfo consoleInfo;
	consoleInfo.Dimensions = { 61,39 };
	consoleInfo.ParentWindow = &window;
	consoleInfo.TextFont = Font("Consolas", 10, Colour(50, 200, 100));
	console = new Console(&consoleInfo);

	while (!window.State.Quit)
	{
		window.UpdateMsg();
	}

	delete textArray;
	delete console;
}