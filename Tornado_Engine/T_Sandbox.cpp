#include "T_Sandbox.h"
#include "Constants.h"

Tornado_Engine::Sandbox::Sandbox()
{
	vec2 = new Vectors::Vec2D(10, 25);
	GFX = new T_Graphics::Graphics;
	/*SmallBall = new Particle_Physics::TParticle(150, 25, 1.0f);
	SmallBall->Radius = 4;
	particles.push_back(SmallBall);*/
	BigBall = new Particle_Physics::TParticle(200, 25, 3.0f);
	BigBall->Radius = 12;
	particles.push_back(BigBall);
}

Tornado_Engine::Sandbox::~Sandbox()
{
	//DELETE THE INSTANCES OVER HERE.
	delete vec2;
	delete GFX;
	for (auto particle : particles) {
		delete particle;
	}
	std::cout << "[ALL INSTANCES DESTROYED SUCCESSFULLY.]" << std::endl;
}

void Tornado_Engine::Sandbox::T_MainLoop()
{
	while (!WindowShouldClose) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_QUIT:
				WindowShouldClose = true;
				break;
			case SDL_EVENT_KEY_DOWN:
				if (event.key.key == SDLK_ESCAPE)
					WindowShouldClose = true;
				if (event.key.key == SDLK_UP)
					PushForce.yComponent = -50 * PIXELS_PER_METER;
				if (event.key.key == SDLK_RIGHT)
					PushForce.xComponent = 50 * PIXELS_PER_METER;
				if (event.key.key == SDLK_DOWN)
					PushForce.yComponent = 50 * PIXELS_PER_METER;
				if (event.key.key == SDLK_LEFT)
					PushForce.xComponent = -50 * PIXELS_PER_METER;
				break;
			case SDL_EVENT_KEY_UP:
				if (event.key.key == SDLK_UP)
					PushForce.yComponent = 0;
				if (event.key.key == SDLK_RIGHT)
					PushForce.xComponent = 0;
				if (event.key.key == SDLK_DOWN)
					PushForce.yComponent = 0;
				if (event.key.key == SDLK_LEFT)
					PushForce.xComponent = 0;
				break;
			}
		}

		//CALL CLEARSCREEN HERE
		GFX->T_ClearScreen(255, 255, 255);

		//GAME LOGIC HERE
		DrawNow(GFX->mainRenderer);

	}
	GFX->T_Terminate();
}

void Tornado_Engine::Sandbox::DrawNow(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	for (auto particle : particles) {
		//Drawing Code Here Like This:
		//draw.T_DrawCirleFilled(renderer, particle->Position.xComponent, particle->Position.yComponent, 5);
		GFX->T_DrawCirleFilled(particle->Position.xComponent, particle->Position.yComponent, particle->Radius);
	}

	//PHYSICS UPDATES
	T_UpdatePhysics();

	SDL_RenderPresent(renderer);
}

void Tornado_Engine::Sandbox::T_Update()
{
	// ANY ONETIME COMMAND CAN BE TYPED HERE.
	GFX->T_GraphicsInit("TORNADO_ENGINE", 1440, 870, SDL_WINDOW_MAXIMIZED);
	GFX->T_CreateRenderer();

	//PHYSICS ONETIME
	T_OneTimePhysicsSetup();
}


void Tornado_Engine::Sandbox::T_UpdatePhysics() {

	//Implement Framerate Control
	int timeToWait = MILLI_SECONDS_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);
	if (timeToWait > 0) {
		SDL_Delay(timeToWait);
	}

	//Implement The Delta Time
	float deltaTime = (SDL_GetTicks() - timePreviousFrame) / 1000.0f;
	if (deltaTime > 0.0333) {
		deltaTime = 0.0333;
	}

	timePreviousFrame = SDL_GetTicks();
	

	//Update Position According To Velocity
	/*particle->Position.xComponent += particle->Velocity.xComponent;
	particle->Position.yComponent += particle->Velocity.yComponent;
									OR 
	particle->Position.Vec2DAddition(particle->Velocity);
									OR
	particle->Position += particle->Velocity * deltaTime;
									*/

	for (auto particle : particles) {
		//ApplyForce
		Vectors::Vec2D wind = Vectors::Vec2D(0.2f * PIXELS_PER_METER, 0.0f);
		particle->T_AddForce(wind);
	}

	for (auto particle : particles) {
		//ApplyForce
		Vectors::Vec2D weight = Vectors::Vec2D(0.0f, particle->Mass * 9.8f * PIXELS_PER_METER);
		particle->T_AddForce(weight);
	}

	for (auto particle : particles) {
		//ApplyForce
		particle->T_AddForce(PushForce);
	}


	//HERE THE ACCELERATION IS 9.8 WHICH IS ACTUALLY THE CHANGE IN VELOCITY PER SECOND OR UNIT TIME, SO, HERE IN EACH FRAME WE ARE ACTUALLY UPDATING OUR VELOCITY BASED ON ACCELERATION.
	for (auto particle : particles) {
		particle->T_EulerIntegrate(deltaTime);
	}

	for (auto particle : particles) {
		//BOUND THE PARTICLE INSIDE THE WINDOW
		if (particle->Position.xComponent - particle->Radius <= 0) {
			particle->Position.xComponent = particle->Radius;
			particle->Velocity.xComponent *= -0.7f;
		}
		else if (particle->Position.xComponent + particle->Radius >= GFX->T_GetWidth()) {
			particle->Position.xComponent = GFX->T_GetWidth() - particle->Radius;
			particle->Velocity *= -0.7f;
		}

		if (particle->Position.yComponent - particle->Radius <= 0) {
			particle->Position.yComponent = particle->Radius;
			particle->Velocity.yComponent *= -0.7f;
		}
		else if (particle->Position.yComponent + particle->Radius >= GFX->T_GetHeight()) {
			particle->Position.yComponent = GFX->T_GetHeight() - particle->Radius;
			particle->Velocity.yComponent *= -0.7f;
		}
	}
}


void Tornado_Engine::Sandbox::T_OneTimePhysicsSetup() {
	//ONE TIME PHYSICS UPDATES
	//particle->Velocity = Vectors::Vec2D(0.0f, 0.0f);
	//particle->Acceleration = Vectors::Vec2D(0.0f, 0.0f);
	PushForce = Vectors::Vec2D(0.0f, 0.0f);
}
