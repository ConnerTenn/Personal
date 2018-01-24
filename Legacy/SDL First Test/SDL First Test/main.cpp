/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <random>
#include <iostream>
#include <thread>

//Screen dimension constants
const int ScreenWidth = 900;
const int ScreenHeight = 600;

SDL_Window *Window, *Window2;

SDL_Surface *TextureSurface;
SDL_Surface *Surface;

SDL_Texture *Texture;

SDL_Renderer *Renderer, *Renderer2;


/*int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	Window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
	Window2 = SDL_CreateWindow("SDL Tutorial2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
	
	//Get window surface
	//Surface = SDL_GetWindowSurface(Window);

	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	Renderer2 = SDL_CreateRenderer(Window2, -1, SDL_RENDERER_ACCELERATED);

	TextureSurface = SDL_LoadBMP("Box.bmp");
	Texture = SDL_CreateTextureFromSurface(Renderer2, TextureSurface);
	SDL_FreeSurface(TextureSurface); TextureSurface = 0;
	

	//SDL_Rect texRect = { 0, 0, ScreenWidth, ScreenHeight };
	//SDL_BlitScaled(Bitmap, NULL, Surface, &texRect);

	srand(0);

	SDL_Event Event;
	bool Run = true;

	while (Run)
	{
		//while (SDL_PollEvent(&Event))
		while (SDL_PollEvent(&Event))
		{
			if (Event.type == SDL_QUIT) { Run = false; }
			else if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_CLOSE) { Run = false; }
			else if (Event.type == SDL_KEYDOWN) { if (Event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) { Run = false; } }
			else { std::cout << Event.type << "\n"; }
		}

		//SDL_RenderClear(Renderer);

		//SDL_Rect texRect = { 0, 0, ScreenWidth, ScreenHeight };
		//SDL_RenderCopy(Renderer, Texture, 0, &texRect);

		SDL_Rect rectangle; rectangle.x = rand() % ScreenWidth; rectangle.y = rand() % ScreenHeight; rectangle.w = rand() % (ScreenWidth - rectangle.x); rectangle.h = rand() % (ScreenHeight - rectangle.y);
		SDL_SetRenderDrawColor(Renderer, rand() % 255, rand() % 255, rand() % 255, 255);
		SDL_RenderDrawRect(Renderer, &rectangle);
		SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);

		static int x = 10, y = 10;
		const Uint8 *key = SDL_GetKeyboardState(0);
		if (key[SDL_SCANCODE_LEFT]) { x--; }
		if (key[SDL_SCANCODE_RIGHT]) { x++; }
		if (key[SDL_SCANCODE_UP]) { y--; }
		if (key[SDL_SCANCODE_DOWN]) { y++; }
		if (x < 0) { x = 0; } if (y < 0) { y = 0; } if (x > ScreenWidth - 70) { x = ScreenWidth - 70; } if (y > ScreenHeight - 70) { y = ScreenHeight - 70; }
		SDL_Rect texRect = { x, y, 70, 70 };
		SDL_RenderCopy(Renderer2, Texture, 0, &texRect);

		SDL_RenderPresent(Renderer);
		SDL_RenderPresent(Renderer2);

		//SDL_UpdateWindowSurface(Window);
	}

	SDL_DestroyWindow(Window);
	Window = NULL;

	SDL_Quit();

	return 0;
}*/


bool DoUpdate = true;
bool Run = true;
std::thread *Thread = 0;

void Update()
{
	while (DoUpdate)
	{
		SDL_Rect rectangle; rectangle.x = rand() % ScreenWidth; rectangle.y = rand() % ScreenHeight; rectangle.w = rand() % (ScreenWidth - rectangle.x); rectangle.h = rand() % (ScreenHeight - rectangle.y);
		SDL_SetRenderDrawColor(Renderer, rand() % 255, rand() % 255, rand() % 255, 255);
		SDL_RenderDrawRect(Renderer, &rectangle);
		SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);

		static int x = 10, y = 10;
		const Uint8 *key = SDL_GetKeyboardState(0);
		if (key[SDL_SCANCODE_LEFT]) { x--; }
		if (key[SDL_SCANCODE_RIGHT]) { x++; }
		if (key[SDL_SCANCODE_UP]) { y--; }
		if (key[SDL_SCANCODE_DOWN]) { y++; }
		if (x < 0) { x = 0; } if (y < 0) { y = 0; } if (x > ScreenWidth - 70) { x = ScreenWidth - 70; } if (y > ScreenHeight - 70) { y = ScreenHeight - 70; }
		SDL_Rect texRect = { x, y, 70, 70 };
		SDL_RenderCopy(Renderer2, Texture, 0, &texRect);

		SDL_RenderPresent(Renderer);
		SDL_RenderPresent(Renderer2);
	}
}

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	Window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
	Window2 = SDL_CreateWindow("SDL Tutorial2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);

	//Get window surface
	//Surface = SDL_GetWindowSurface(Window);

	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	Renderer2 = SDL_CreateRenderer(Window2, -1, SDL_RENDERER_ACCELERATED);


	TextureSurface = SDL_LoadBMP("Box.bmp");
	Texture = SDL_CreateTextureFromSurface(Renderer2, TextureSurface);
	SDL_FreeSurface(TextureSurface); TextureSurface = 0;

	//SDL_Rect texRect = { 0, 0, ScreenWidth, ScreenHeight };
	//SDL_BlitScaled(Bitmap, NULL, Surface, &texRect);

	srand(0);

	SDL_Event Event;
	const Uint8 *key = SDL_GetKeyboardState(0);

	while (SDL_WaitEvent(&Event) && Run)
	{
		if (Event.type == SDL_QUIT) { Run = false; }
		else if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_CLOSE) { Run = false; }
		else if (Event.type == SDL_KEYDOWN) { if (Event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) { Run = false; } }
		else { std::cout << Event.type << "\n"; }

		key = SDL_GetKeyboardState(0);
		if (Event.type == SDL_KEYDOWN && key[SDL_SCANCODE_A])
		{
			if (!Thread) { DoUpdate = true; Thread = new std::thread(Update); }
		}
		if (Event.type == SDL_KEYDOWN && key[SDL_SCANCODE_B])
		{
			if (Thread) { DoUpdate = false; Thread->join(); delete Thread; Thread = 0; }
		}
	}

	if (Thread) { DoUpdate = false; Thread->join(); delete Thread; Thread = 0; }

	SDL_FreeSurface(Surface);

	SDL_DestroyWindow(Window);
	Window = NULL;

	SDL_Quit();

	return 0;
}