#pragma once
#include "Vectors.h"
#include "T_Graphics.h"
#include "TParticle.h"
#include <vector>

namespace Tornado_Engine {
	class Sandbox
	{
	public:
		Sandbox();
		~Sandbox();

		void T_Update();
		void T_MainLoop();
		void DrawNow(SDL_Renderer* renderer);
		void T_DrawPolygon(SDL_Renderer* renderer, int x, int y, const std::vector<Vectors::Vec2D>& vertices);

	private:
		Vectors::Vec2D* vec2;
		T_Graphics::Graphics* GFX;
		Particle_Physics::TParticle* particle;

		bool WindowShouldClose = false;
	};
}
