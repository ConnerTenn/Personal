
#include "WinLib.h"

Container *container1;
Container *container2;
//Container *container3;
TextBox *textbox;
Texture *texture;

Window *win;


void Callback(CallbackData message)
{
	if (message.message == WM_KEYDOWN)
	{
		InvalidateRect(win->Hwnd, NULL, true);
	}
}


INT WINAPI WinMain(HINSTANCE HInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	win = new Window(800, 500, HInstance, iCmdShow, Callback);
	win->Name = "WinLib_1-8";
	win->Create();

	container1 = win->CreateContainer(0, 0, 800, 400, 2); container1->Scale(0.5, 0.5);
	container2 = container1->CreateContainer(100, 100, 50, 50);

	//Window win2(600, 400, HInstance, iCmdShow);
	//win2.Name = "WinLib_1-7";
	//win2.Create();

	//container3 = win2.CreateContainer(0, 0, 600, 400);

	texture = new Texture("texture.bmp");// , &win.Ps);

	textbox = new TextBox(10, 200, 400, 100, win, Font("consolas"));
	textbox->EnableNewLines = true;

	bool done = false;

	while (!done)
	{
		win->UpdateMsg();

		//InvalidateRect(win->Hwnd, NULL, true);

		container1->Clear();
		container2->Clear();

		container1->FillRectangle(0, 0, 600, 500, Colour(255, 000, 000));
		container2->FillRectangle(0, 0, 500, 500, Colour(000, 255, 000));

		textbox->Update();
		textbox->Render();
		
		win->Render();

		if (win->State.Quit == true)// || win2.State.Quit == true)
		{
			done = true;
		}
	}
	
	while (!done && false)
	{
		{/*Event Handler*/ }
		{
			win->UpdateMsg();
			//win2.UpdateMsg();

			if (win->State.Quit == true)// || win2.State.Quit == true)
			{
				done = true;
			}
		}

		{/*Update*/ }
		{
			textbox->Update();

		}

		{/*Render*/ }
		{
			container1->Clear();
			container2->Clear();
			//container3->Clear();

			container1->FillRectangle(0, 0, 600, 500, Colour(255, 000, 000));
			container2->FillRectangle(0, 0, 500, 500, Colour(000, 255, 000));
			container1->DrawRectangle(0, 0, 299, 299, Colour(127, 127, 127), 5);
			container1->DrawLine(2, 0, 2, 500, Colour(255, 255, 000), 3);
			container1->FillEllipse(10, 10, 100, 100, Colour(127, 127, 127), TAU / 8.0, TAU / 4.0);
			container1->DrawEllipse(10, 10, 100, 100, Colour(000, 000, 000), TAU / 8.0, TAU / 4.0, 3);
			container1->DrawEllipse(35, 35, 50, 50, Colour(000, 000, 000), TAU / 8.0, TAU / 4.0, 3);
			container1->DrawImage(500, 0, texture->Width / 2, texture->Height / 2, texture);

			textbox->Render();

			win->Render();
			//win2.Render();
		}
	}
	delete texture;
	delete win;
}

