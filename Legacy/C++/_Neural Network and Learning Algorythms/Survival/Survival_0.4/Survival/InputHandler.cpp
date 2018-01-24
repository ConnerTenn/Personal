
#include "InputHandler.h"

InputHandler::InputHandler(Window *parentWindow)
{
	ParentWindow = parentWindow;
}

void InputHandler::Update()
{
	//Keys
	for (int i = 0; i < 255; i++)
	{
		Key *key = &KeyState[i];
		if (key->Pressed)
		{
			if (key->FlipCounter <= 0)
			{
				key->Flip = !key->Flip;
			}
			else
			{
				key->FlipCounter -= ParentWindow->Delta;
			}
			if (key->Hold)
			{
				key->Press = false;
			}
			else
			{
				key->Press = true;
				key->Hold = true;
			}
		}
		else
		{
			key->Hold = false;
			key->Press = false;
			key->FlipCounter = key->FlipDelay;
			key->Flip = false;
		}
	}

	//Mouse
	Mouse *mouse = &MouseState;
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(ParentWindow->Hwnd, &point);
	mouse->X = point.x; mouse->Y = point.y;
	if (mouse->X < 0 || mouse->X > ParentWindow->Width) { mouse->X = -1; mouse->Y = -1; }
	if (mouse->Y < 0 || mouse->Y > ParentWindow->Height) { mouse->X = -1; mouse->Y = -1; }
	if (GetFocus() != ParentWindow->Hwnd) { mouse->X = -1; mouse->Y = -1; }
	if (mouse->X != -1)
	{

	}
}

