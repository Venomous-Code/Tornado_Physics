#include "TGraphics.h"

void TGraphics::SDL_Setup::T_CreateWindow(const char* WindowName, unsigned int WindowWidth, unsigned int WindowHeight)
{
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(WindowName, WindowWidth, WindowHeight, SDL_WINDOW_MAXIMIZED);
	renderer = SDL_CreateRenderer(window, NULL);

	if (window == NULL) {
		throw std::runtime_error("[ERROR]:- TORNADO FAILED TO INITIALIZE THE WINDOW.");
	}

	T_EventLoop();

}

void TGraphics::SDL_Setup::T_EventLoop()
{
	TDrawing draw;
	Vectors::Vec2D points0(550, 190);
	Vectors::Vec2D points1(325, 255);
	Vectors::Vec2D points2(612, 222);
	Vectors::Vec2D points3(625, 475);

	std::vector<Vectors::Vec2D> vertices;
	vertices.push_back(points0);
	vertices.push_back(points1);
	vertices.push_back(points2);
	vertices.push_back(points3);

	int Cx = 50;
	int Cy = 50;

	while (!WindowShouldClose) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				WindowShouldClose = true;
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		//GAME LOGIC
		
		//DRAW CALLS HERE!!!
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		//draw.T_DrawCircle(renderer, 50, 50, 15);
		//draw.T_DrawLine(renderer, 50, 65, 22, 99);
		//draw.T_DrawCirleFilled(renderer, Cx, Cy, 15);
		//draw.T_DrawPolygon(renderer, 225, 350, vertices);
		

		SDL_RenderPresent(renderer);

	}

	//DESTROY
	T_TerminateTornado();
}

void TGraphics::SDL_Setup::T_TerminateTornado()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void TGraphics::TDrawing::T_DrawCircle(SDL_Renderer* renderer, int Cx, int Cy, int Radius)
{
	int x = 0;
	int y = Radius;
	int d = 3 - 2 * Radius;

	while (x <= y) {
		SDL_RenderPoint(renderer, Cx + x, Cy + y);
		SDL_RenderPoint(renderer, Cx - x, Cy + y);
		SDL_RenderPoint(renderer, Cx + x, Cy - y);
		SDL_RenderPoint(renderer, Cx - x, Cy - y);
		SDL_RenderPoint(renderer, Cx + y, Cy + x);
		SDL_RenderPoint(renderer, Cx - y, Cy + x);
		SDL_RenderPoint(renderer, Cx + y, Cy - x);
		SDL_RenderPoint(renderer, Cx - y, Cy - x);
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

void TGraphics::TDrawing::T_DrawLine(SDL_Renderer* renderer, int startX, int startY, int endX, int endY)
{
	SDL_RenderLine(renderer, startX, startY, endX, endY);
}

void TGraphics::TDrawing::T_DrawCirleFilled(SDL_Renderer* renderer, int Cx, int Cy, int Radius)
{
	int x = 0;
	int y = Radius;
	int d = 3 - 2 * Radius;

	while (x <= y) {
		// draw horizontal spans between symmetric x points
		SDL_RenderLine(renderer, Cx - x, Cy + y, Cx + x, Cy + y);
		SDL_RenderLine(renderer, Cx - x, Cy - y, Cx + x, Cy - y);
		SDL_RenderLine(renderer, Cx - y, Cy + x, Cx + y, Cy + x);
		SDL_RenderLine(renderer, Cx - y, Cy - x, Cx + y, Cy - x);

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

void TGraphics::TDrawing::T_DrawPolygon(SDL_Renderer* renderer,int x, int y, const std::vector<Vectors::Vec2D>& vertices)
{
	for (int i = 0; i < vertices.size(); i++) {
		int currIndex = i;
		int nextIndex = (i + 1) % vertices.size();
		SDL_RenderLine(renderer, vertices[currIndex].xComponent, vertices[currIndex].yComponent, vertices[nextIndex].xComponent, vertices[nextIndex].yComponent);
	}
	T_DrawCirleFilled(renderer, x, y, 1);
}