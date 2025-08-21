#pragma once
#include <iostream>
#include <SDL3\SDL.h>
#define VIDEO_MODE SDL_INIT_VIDEO

namespace T_Graphics {
	class Graphics
	{
	public:
		void T_GraphicsInit(const char* windowName, unsigned int windowWidth, unsigned int windowHeight, SDL_WindowFlags mainWindowFlags);
		void T_CreateRenderer(SDL_Renderer* mainRenderer);
		void T_ClearScreen(SDL_Renderer* mainRenderer, int Red, int Green, int Blue);
		void T_Terminate(SDL_Renderer* mainRenderer);
		void T_DrawCircle(SDL_Renderer* mainRenderer, int Cx, int Cy, int Radius);
		void T_DrawLine(SDL_Renderer* mainRenderer, int startX, int startY, int endX, int endY);
		void T_DrawCirleFilled(SDL_Renderer* mainRenderer, int Cx, int Cy, int Radius);

	private:
		SDL_Window* mainWindow;
	};
}
