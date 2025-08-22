#pragma once
#include <iostream>
#include <SDL3\SDL.h>
#include "Vectors.h"
#include <vector>

namespace T_Graphics {
	class Graphics
	{
	public:
		void T_GraphicsInit(const char* windowName, unsigned int windowWidth, unsigned int windowHeight, SDL_WindowFlags mainWindowFlags);
		void T_CreateRenderer();
		void T_ClearScreen(int Red, int Green, int Blue);
		void T_Terminate();
		void T_DrawCircle(int Cx, int Cy, int Radius);
		void T_DrawLine(int startX, int startY, int endX, int endY);
		void T_DrawCirleFilled(int Cx, int Cy, int Radius);
		void T_DrawPolygon(int x, int y, const std::vector<Vectors::Vec2D>& vertices);

		SDL_Window* mainWindow;
		SDL_Renderer* mainRenderer;
	private:
	};
}
