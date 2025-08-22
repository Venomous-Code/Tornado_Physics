#pragma once
#include "T_Graphics.h"
#include "TParticle.h"

namespace Tornado_Engine {
	class Sandbox
	{
	public:
		Sandbox();
		~Sandbox();

		void T_Update();
		void T_MainLoop();
		void DrawNow(SDL_Renderer* renderer);

		void T_UpdatePhysics();
		void T_OneTimePhysicsSetup();

	private:
		Vectors::Vec2D* vec2;
		T_Graphics::Graphics* GFX;
		Particle_Physics::TParticle* particle;

		bool WindowShouldClose = false;
		uint32_t timePreviousFrame;
	};
}
