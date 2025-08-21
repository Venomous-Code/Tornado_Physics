#pragma once
#include "Vectors.h"
#include "T_Graphics.h"
#include <vector>

namespace Tornado_Engine {
	class Sandbox
	{
	public:
		Sandbox();
		~Sandbox();

		void T_Update();
		void T_MainLoop();
		void DrawNow();
		void T_DrawPolygon(int x, int y, const std::vector<Vectors::Vec2D>& vertices);

	private:
		Vectors::Vec2D* vec2;
		T_Graphics::Graphics* GFX;
		SDL_Renderer* mainRenderer;

		bool WindowShouldClose = false;
	};
}
