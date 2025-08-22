#include "T_Graphics.h"

void T_Graphics::Graphics::T_GraphicsInit(const char* windowName, unsigned int windowWidth, unsigned int windowHeight, SDL_WindowFlags mainWindowFlags)
{
	SDL_Init(SDL_INIT_VIDEO);
	mainWindow = SDL_CreateWindow(windowName, windowWidth, windowHeight, mainWindowFlags);
}

void T_Graphics::Graphics::T_CreateRenderer()
{
	mainRenderer = SDL_CreateRenderer(mainWindow, NULL);
}

void T_Graphics::Graphics::T_ClearScreen(int Red, int Green, int Blue)
{
	SDL_SetRenderDrawColor(mainRenderer, Red, Green, Blue, 255);
	SDL_RenderClear(mainRenderer);
}

void T_Graphics::Graphics::T_Terminate()
{
	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
}

void T_Graphics::Graphics::T_DrawCircle(int Cx, int Cy, int Radius)
{
	int x = 0;
	int y = Radius;
	int d = 3 - 2 * Radius;

	while (x <= y) {
		SDL_RenderPoint(mainRenderer, Cx + x, Cy + y);
		SDL_RenderPoint(mainRenderer, Cx - x, Cy + y);
		SDL_RenderPoint(mainRenderer, Cx + x, Cy - y);
		SDL_RenderPoint(mainRenderer, Cx - x, Cy - y);
		SDL_RenderPoint(mainRenderer, Cx + y, Cy + x);
		SDL_RenderPoint(mainRenderer, Cx - y, Cy + x);
		SDL_RenderPoint(mainRenderer, Cx + y, Cy - x);
		SDL_RenderPoint(mainRenderer, Cx - y, Cy - x);
		if (d < 0) {
			d = d + 4 * x + 6;
		}
		else {
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}

void T_Graphics::Graphics::T_DrawLine(int startX, int startY, int endX, int endY)
{
	SDL_RenderLine(mainRenderer, startX, startY, endX, endY);
}

void T_Graphics::Graphics::T_DrawCirleFilled(int Cx, int Cy, int Radius)
{
	int x = 0;
	int y = Radius;
	int d = 3 - 2 * Radius;

	while (x <= y) {
		// draw horizontal spans between symmetric x points
		SDL_RenderLine(mainRenderer, Cx - x, Cy + y, Cx + x, Cy + y);
		SDL_RenderLine(mainRenderer, Cx - x, Cy - y, Cx + x, Cy - y);
		SDL_RenderLine(mainRenderer, Cx - y, Cy + x, Cx + y, Cy + x);
		SDL_RenderLine(mainRenderer, Cx - y, Cy - x, Cx + y, Cy - x);

		if (d < 0) {
			d = d + 4 * x + 6;
		}
		else {
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}
