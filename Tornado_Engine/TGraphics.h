#pragma once
#include <iostream>
#include "SDL3\SDL.h"
#include <vector>
#include "Vectors.h"
#include <chrono>

namespace TGraphics {

	class SDL_Setup
	{
	public:

		void T_CreateWindow(const char* WindowName, unsigned int WindowWidth, unsigned int WindowHeight);

	private:
		//METHODS
		void T_EventLoop();
		void T_TerminateTornado();

		//DATA MEMBERS
		SDL_Window* window;
		SDL_Renderer* renderer;
		/*SDL_Texture* bitmapTexture;
		SDL_Surface* bitmapSurface;*/
		bool WindowShouldClose = false;


	};

	class TDrawing {
	public:

		void T_DrawCircle(SDL_Renderer* renderer, int Cx, int Cy, int Radius);
		void T_DrawLine(SDL_Renderer* renderer, int startX, int startY, int endX, int endY);
		void T_DrawCirleFilled(SDL_Renderer* renderer, int Cx, int Cy, int Radius);
		void T_DrawPolygon(SDL_Renderer* renderer, int x, int y, const std::vector<Vectors::Vec2D>& vertices);

	private:

	};

}