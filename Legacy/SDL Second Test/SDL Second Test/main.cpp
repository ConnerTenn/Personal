/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <random>
#include <iostream>
#include <time.h>

//Screen dimension constants
const int ScreenWidth = 1600;//900;
const int ScreenHeight = 800;//600;

SDL_Window *Window;

SDL_Surface *Surface, *WinSurface;

SDL_Texture *SurfaceTexture;

SDL_Renderer *Renderer, *WinRenderer;


bool DoUpdate = true;
bool Run = true;


int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	Window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);

	//Get window surface
	WinSurface = SDL_GetWindowSurface(Window);

	WinRenderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_RendererInfo info;  SDL_GetRendererInfo(WinRenderer, &info);
	Surface = SDL_CreateRGBSurface(info.flags, info.max_texture_width, info.max_texture_width, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	//Surface = WinSurface;
	
	//SDL_CreateTexture()

	Renderer = SDL_CreateSoftwareRenderer(Surface); //SurfaceTexture = SDL_CreateTextureFromSurface(Renderer, Surface); SDL_SetRenderTarget(Renderer, SurfaceTexture);
	//Renderer = WinRenderer;

	srand(0);

	SDL_Event Event;
	const Uint8 *key = SDL_GetKeyboardState(0);

	while (Run)
	{
		while (SDL_PollEvent(&Event))
		{
			if (Event.type == SDL_QUIT) { Run = false; }
			else if (Event.type == SDL_WINDOWEVENT && Event.window.event == SDL_WINDOWEVENT_CLOSE) { Run = false; }
			else if (Event.type == SDL_KEYDOWN) { if (Event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) { Run = false; } }
			//else { std::cout << Event.type << "\n"; }
		}

		SDL_Rect rectangle; rectangle.x = rand() % ScreenWidth; rectangle.y = rand() % ScreenHeight; rectangle.w = rand() % (ScreenWidth - rectangle.x); rectangle.h = rand() % (ScreenHeight - rectangle.y);
		SDL_SetRenderDrawColor(Renderer, rand() % 255, rand() % 255, rand() % 255, 255);
		SDL_RenderDrawRect(Renderer, &rectangle);
		//std::cout << (Renderer, 0, 0, 0, 0) << "\n";
		
		//SDL_RenderPresent(Renderer);

		//SurfaceTexture = SDL_CreateTextureFromSurface(Renderer, Surface);

		SDL_Rect texRect = { 0,0,ScreenWidth,ScreenHeight };
		//SDL_RenderCopy(WinRenderer, SurfaceTexture, 0, &texRect);

		long t1 = clock();
		for (int i = 0; i < 1; ++i)
		{
			//SDL_BlitSurface(Surface, &texRect, WinSurface, &texRect);
			SDL_LowerBlit(Surface, &texRect, WinSurface, &texRect);
		}
		std::cout << clock() - t1 << "\n";

		//SDL_RenderPresent(WinRenderer);
		SDL_UpdateWindowSurface(Window);
	}


	SDL_FreeSurface(Surface);

	SDL_DestroyWindow(Window);
	Window = NULL;

	SDL_Quit();

	return 0;
}