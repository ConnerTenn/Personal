
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

	//textArray->Draw();
	//window->WindowSurface->CopySurface({ {900/2,000}, { textArray->TextSurface->Dimensions.X + 900/2, textArray->TextSurface->Dimensions.Y + 000 } }, textArray->TextSurface, { {0,0}, { textArray->TextSurface->Dimensions.X, textArray->TextSurface->Dimensions.Y} });
	//textArray->Resize({ textArray->Dimensions.X + 1, textArray->Dimensions.Y });

	static int i = 0;
	console->Draw();
	window->WindowSurface->CopySurface({ { 0,000 },{ console->TextSurface->Dimensions.X, console->TextSurface->Dimensions.Y + 000 } }, console->TextSurface, { { 0,0 },{ console->TextSurface->Dimensions.X, console->TextSurface->Dimensions.Y } });

	window->Draw();
	i++;
}

void Callback(Window *window, MessageData message, void *data)
{
	//static int i = 0;
	if (message == WM_KEYDOWN)
	{
		if (message.WParam() == WL_UP) { console->MoveCursor(UP); }
		else if (message.WParam() == WL_RIGHT) { console->MoveCursor(RIGHT); }
		else if (message.WParam() == WL_DOWN) { console->MoveCursor(DOWN); }
		else if (message.WParam() == WL_LEFT) { console->MoveCursor(LEFT); }
		else if (message.WParam() == WL_BACKSPACE) { console->BackspaceChar(); }
		else if (message.WParam() == WL_RETURN) { console->WriteChar('\n'); }
		else if (message.WParam() != WL_SHIFT)
		{
			if (window->Input->KeyState[WL_SHIFT].Pressed)
			{
				console->WriteChar((char)message.WParam());
			}
			else
			{
				console->WriteChar((char)message.WParam() - ('A'-'a'));
			}
		}
	}

	if (message == WM_CREATE || message == WM_KEYDOWN || message == WM_KEYUP || message == WM_LBUTTONDOWN || message == WM_LBUTTONUP || message == WM_RBUTTONDOWN || message == WM_RBUTTONUP || message == WM_MBUTTONDOWN || message == WM_MBUTTONUP)
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

	std::string stringI = "Hello, Test String!", string; for (int i = 0; i < 10000; i++, string = string + stringI) {}
	textArray->WriteString({ 0,0 }, string);

	ConsoleInfo consoleInfo;
	consoleInfo.Dimensions = { 61,39 };
	consoleInfo.ParentWindow = &window;
	consoleInfo.TextFont = Font("Consolas", 10, Colour(50, 200, 100));
	console = new Console(&consoleInfo);

	console->Text.push_back("Test String 1");
	console->Text.push_back("Test String 2");
	console->Text.push_back("Test String 3");
	console->Text.push_back("");
	console->Cursor = { 5, 3 };

	console->Write("--");
	console->WriteChar('!');
	console->Cursor.X = 0;
	console->BackspaceChar();

	while (!window.State.Quit)
	{
		window.UpdateMsg();
	}

	delete textArray;
	delete console;
}