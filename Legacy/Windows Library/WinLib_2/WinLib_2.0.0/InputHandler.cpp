
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
				key->FlipCounter -= ParentWindow->State.Delta;
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
	//Mouse *mouse = &MouseState;
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(ParentWindow->Hwnd, &point);
	MouseState.X = point.x; MouseState.Y = point.y;
	if (MouseState.X < 0 || MouseState.X > ParentWindow->Dimensions.X) { MouseState.X = -1; MouseState.Y = -1; }
	if (MouseState.Y < 0 || MouseState.Y > ParentWindow->Dimensions.Y) { MouseState.X = -1; MouseState.Y = -1; }
	if (GetFocus() != ParentWindow->Hwnd) { MouseState.X = -1; MouseState.Y = -1; }
}

