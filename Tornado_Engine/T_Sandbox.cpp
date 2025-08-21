#include "T_Sandbox.h"

Tornado_Engine::Sandbox::Sandbox()
{
	vec2 = new Vectors::Vec2D(10, 25);
	GFX = new T_Graphics::Graphics();
}

Tornado_Engine::Sandbox::~Sandbox()
{
	//DELETE THE INSTANCES OVER HERE.
	delete vec2;
	delete GFX;
}

void Tornado_Engine::Sandbox::T_MainLoop()
{
	while (!WindowShouldClose) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				WindowShouldClose = true;
			}
		}

		//CALL CLEARSCREEN HERE
		GFX->T_ClearScreen(mainRenderer, 255, 255, 255);

		//GAME LOGIC HERE
		DrawNow();

	}
	GFX->T_Terminate(mainRenderer);
}

void Tornado_Engine::Sandbox::DrawNow()
{
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);

	//Drawing Code Here Like This:
	//draw.T_DrawCirleFilled(renderer, particle->Position.xComponent, particle->Position.yComponent, 5);

	SDL_RenderPresent(mainRenderer);
}

void Tornado_Engine::Sandbox::T_Update()
{
	// ANY ONETIME COMMAND CAN BE TYPED HERE.
}

void Tornado_Engine::Sandbox::T_DrawPolygon(int x, int y, const std::vector<Vectors::Vec2D>& vertices)
{
	for (int i = 0; i < vertices.size(); i++) {
		int currIndex = i;
		int nextIndex = (i + 1) % vertices.size();
		SDL_RenderLine(mainRenderer, vertices[currIndex].xComponent, vertices[currIndex].yComponent, vertices[nextIndex].xComponent, vertices[nextIndex].yComponent);
	}
	GFX->T_DrawCirleFilled(mainRenderer, x, y, 1);
}
