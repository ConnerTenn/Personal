
#include "WinLib.h"

Container *container1;
Container *container2;
Container *container3;
TextBox *textbox;

INT WINAPI WinMain(HINSTANCE HInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	Window win(800, 500, HInstance, iCmdShow);
	win.Name = "WinLib_1-7";
	win.Create();

	container1 = win.CreateContainer(0, 0, 800, 400, 2); container1->Scale(0.5, 0.5);
	container2 = container1->CreateContainer(100, 100, 50, 50);

	Window win2(600, 400, HInstance, iCmdShow);
	win2.Name = "WinLib_1-7";
	win2.Create();

	container3 = win2.CreateContainer(0, 0, 600, 400);

	Texture texture("texture.bmp");// , &win.Ps);

	textbox = new TextBox(10, 200, 400, 100, &win, Font("consolas"));
	textbox->EnableNewLines = true;
	
	bool done = false;
	while (!done)
	{
		{/*Event Handler*/}
		{
			win.UpdateMsg();
			win2.UpdateMsg();

			if (win.State.Quit == true || win2.State.Quit == true)
			{
				done = true;
			}
		}

		{/*Update*/} 
		{
			textbox->Update();

			static float n = 0;
			container1->SetPos((int)(sin(n) * 50), (int)(-cos(n) * 50));
			container2->SetPos((int)(sin(2.0 * n) * 50 + 100), (int)(cos(2.0 * n) * 50 + 100));
			n += (float)(win.Delta * 0.01);
		}

		{/*Render*/}
		{
			container1->Clear();
			container2->Clear();
			container3->Clear();

			container1->FillRectangle(0, 0, 600, 500, Colour(255, 000, 000));
			container2->FillRectangle(0, 0, 500, 500, Colour(000, 255, 000));
			container1->DrawRectangle(0, 0, 299, 299, Colour(127, 127, 127), 5);
			container1->DrawLine(2, 0, 2, 500, Colour(255, 255, 000), 3);
			container1->FillEllipse(10, 10, 100, 100, Colour(127, 127, 127), TAU / 8.0, TAU / 4.0);
			container1->DrawEllipse(10, 10, 100, 100, Colour(000, 000, 000), TAU / 8.0, TAU / 4.0, 3);
			container1->DrawEllipse(35, 35, 50, 50, Colour(000, 000, 000), TAU / 8.0, TAU / 4.0, 3);
			container1->DrawImage(500, 0, texture.Width / 2, texture.Height / 2, &texture);
			container3->FillRectangle(10, 10, 100, 200, Colour(20, 20, 20));
			container3->DrawText(0, 0, "[conner@winlib]$ listcommands\n\
SetPos\n\
Translate\n\
Scale\n\
Resize\n\
\n\
Clear\n\
FillRectangle\n\
DrawRectangle\n\
FillEllipse\n\
DrawEllipse\n\
DrawLine\n\
DrawImage\n\
DrawText\n\
\n\
[conner@winlib]$ \v", Font("arial", Colour(0, 255, 0)));
			container3->DrawText(300, 100, "DeltaTime:" + std::to_string(win2.Delta) + "ms", Font("Consolas", 15, Colour(0, 255, 0), 0));
			container3->DrawText(300, 130, "X:" + std::to_string(win2.Input->MouseState.X) + "\nY:" + std::to_string(win2.Input->MouseState.Y), Font("Consolas", 15, Colour(0, 255, 0), 0));

			for (int i = 0; i < 10; i++)
			{
				container3->DrawLine(10 + i * 10 * 5, 290, 10 + i * 10 * 5, 300, Colour(0, 255, 0));
			}
			for (int i = 0; i < 255; i++)
			{
				container3->DrawRectangle(10 + (i % 50) * 10, 300 + (i / 50) * 10, 10, 10, Colour(0, 255, 0));
				if (win2.Input->KeyState[i].Pressed)
				{
					container3->FillRectangle(10 + (i % 50) * 10, 300 + (i / 50) * 10, 10, 10, Colour(0, 255, 0));
				}
			}
			std::string text = "";
			for (int i = 0; i < 255; i++)
			{
				if (win2.Input->KeyState[i].Pressed)
				{
					text += std::to_string(i) + "\n";
				}				
			}
			container3->DrawText(530, 300, text, Font(Colour(0, 255, 0)));

			if (container1->State.Focus)
			{
				container3->FillRectangle(100, 230, 10, 10, Colour(000, 000, 255));
			}
			else
			{
				container3->DrawRectangle(100, 230, 10, 10, Colour(000, 000, 255));
			}
			textbox->Render();

			win.Render();
			win2.Render();
		}
	}
}

