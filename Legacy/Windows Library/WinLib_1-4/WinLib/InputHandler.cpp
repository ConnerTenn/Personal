
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

	if (mouse->DoubleClick) { mouse->DoubleClick = false; }
	if (mouse->Click) { mouse->Click = false; }
	if (mouse->FirstPressState)
	{
		if (mouse->LPressed)
		{
			mouse->FirstPressState = false;
			mouse->FirstReleaseState = true;
		}
	}
	else if (mouse->FirstReleaseState)
	{
		if (mouse->LPressed)
		{
			mouse->FirstReleaseCounter += ParentWindow->Delta;
		}
		else
		{
			mouse->Click = true;
			if (mouse->FirstReleaseCounter <= mouse->DoubleClickDelay)
			{
				mouse->FirstReleaseState = false;
				mouse->SecondPressState = true;
			}
			else
			{
				mouse->FirstReleaseState = false;
				mouse->FirstPressState = true;
			}
			mouse->FirstReleaseCounter = 0;
		}
	}
	else if (mouse->SecondPressState)
	{
		if (!mouse->LPressed)
		{
			mouse->SecondPressCounter += ParentWindow->Delta;
			if (mouse->SecondPressCounter > mouse->DoubleClickDelay)
			{
				mouse->SecondPressState = false;
				mouse->FirstPressState = true;
				mouse->SecondPressCounter = 0;
			}
		}
		else
		{
			mouse->Click = true;
			mouse->DoubleClick = true;
			mouse->SecondPressState = false;
			mouse->WaitReleaseState = true;
			mouse->SecondPressCounter = 0;
		}
	}
	else if (mouse->WaitReleaseState)
	{
		if (!mouse->LPressed)
		{
			mouse->WaitReleaseState = false;
			mouse->FirstPressState = true;
		}
	}
	/*if (!mouse->FirstDownState)
	{
		if (mouse->LPressed)
		{
			mouse->FirstDownCounter += ParentWindow->Delta;
		}
		else
		{
			if (mouse->FirstDownCounter < mouse->DoubleClickDelay && mouse->FirstDownCounter)
			{
				mouse->FirstDownState = true;
			}
			else
			{
				mouse->FirstDownState = false;
			}
			mouse->FirstDownCounter = 0;
		}
	}
	else
	{
		mouse->Click = true;
		if (!mouse->LPressed)
		{
			mouse->FirstUpCounter += ParentWindow->Delta;
		}
		else
		{
			if (mouse->FirstUpCounter < mouse->DoubleClickDelay && mouse->FirstUpCounter)
			{
				mouse->DoubleClick = true;
				mouse->Click = false;
			}
			mouse->FirstUpCounter = 0;
			mouse->FirstDownState = false;
		}
	}*/
}

