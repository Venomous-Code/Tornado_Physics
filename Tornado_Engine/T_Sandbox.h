#pragma once
#include "T_Graphics.h"
#include "T_Body.h"
#include "Force.h"

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
		Body_Physics::T_Body* SmallBall;
		Body_Physics::T_Body* BigBall;
		Vectors::Vec2D PushForce;
		SDL_Rect Fluid;
		Vectors::Vec2D mouseCursor;
		
		Vectors::Vec2D Anchor = Vectors::Vec2D(0.0f, 0.0f);
		float K = 100.0f;
		float RestLength = 200.0f;

		//DATA MEMBERS
		bool WindowShouldClose = false;
		bool LeftMouseButtonDown = false;
		uint32_t timePreviousFrame;

		//VECTORS
		std::vector<Body_Physics::T_Body*> bodies;
	};
}
