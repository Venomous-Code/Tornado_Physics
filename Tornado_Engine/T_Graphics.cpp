#include "T_Graphics.h"

void T_Graphics::Graphics::T_GraphicsInit(const char* windowName, unsigned int windowWidth, unsigned int windowHeight, SDL_WindowFlags mainWindowFlags)
{
	SDL_Init(SDL_INIT_VIDEO);
	mainWindow = SDL_CreateWindow(windowName, windowWidth, windowHeight, mainWindowFlags);
}

void T_Graphics::Graphics::T_CreateRenderer()
{
	mainRenderer = SDL_CreateRenderer(mainWindow, NULL);
}

void T_Graphics::Graphics::T_ClearScreen(int Red, int Green, int Blue)
{
	SDL_SetRenderDrawColor(mainRenderer, Red, Green, Blue, 255);
	SDL_RenderClear(mainRenderer);
}

void T_Graphics::Graphics::T_Terminate()
{
	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
}

void T_Graphics::Graphics::T_DrawCircle(int Cx, int Cy, int Radius, float Angle)
{
	/*int x = 0;
	int y = Radius;
	int d = 3 - 2 * Radius;

	while (x <= y) {
		SDL_RenderPoint(mainRenderer, Cx + x, Cy + y);
		SDL_RenderPoint(mainRenderer, Cx - x, Cy + y);
		SDL_RenderPoint(mainRenderer, Cx + x, Cy - y);
		SDL_RenderPoint(mainRenderer, Cx - x, Cy - y);
		SDL_RenderPoint(mainRenderer, Cx + y, Cy + x);
		SDL_RenderPoint(mainRenderer, Cx - y, Cy + x);
		SDL_RenderPoint(mainRenderer, Cx + y, Cy - x);
		SDL_RenderPoint(mainRenderer, Cx - y, Cy - x);
		if (d < 0) {
			d = d + 4 * x + 6;
		}
		else {
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
	}*/

	// This part of the function remains the same.
	// We are using the Midpoint Circle Algorithm to draw the outline of the circle itself.
	// This part is independent of the rotation, as a circle's outline doesn't change when rotated.
	int x = 0;
	int y = Radius;
	int d = 3 - 2 * Radius;

	while (x <= y) {
		// Plotting points in all 8 octants to create the circle shape.
		SDL_RenderPoint(mainRenderer, Cx + x, Cy + y);
		SDL_RenderPoint(mainRenderer, Cx - x, Cy + y);
		SDL_RenderPoint(mainRenderer, Cx + x, Cy - y);
		SDL_RenderPoint(mainRenderer, Cx - x, Cy - y);
		SDL_RenderPoint(mainRenderer, Cx + y, Cy + x);
		SDL_RenderPoint(mainRenderer, Cx - y, Cy + x);
		SDL_RenderPoint(mainRenderer, Cx + y, Cy - x);
		SDL_RenderPoint(mainRenderer, Cx - y, Cy - x);

		if (d < 0) {
			d = d + 4 * x + 6;
		}
		else {
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
	}

	// Now we will add the new functionality to draw a rotating radius line.

	// Step 1: Convert the angle from degrees to radians.
	// The standard C++ trigonometric functions (sin and cos) work with radians.
	float angleInRadians = Angle * (PI / 180.0f);

	// Step 2: Calculate the endpoint of the radius line using basic trigonometry.
	// The endpoint is a point on the circumference of the circle.
	// The formula for a point on a circle is based on the radius and the angle.
	int endX = Cx + static_cast<int>(Radius * cos(angleInRadians));
	int endY = Cy + static_cast<int>(Radius * sin(angleInRadians));

	// The mathematical formulas are:
	// x = Cx + R * cos(theta)
	// y = Cy + R * sin(theta)
	// Where (x, y) is the endpoint, (Cx, Cy) is the center, R is the radius, and theta is the angle in radians.

	// Step 3: Draw the line from the center to the calculated endpoint.
	// We use the SDL_RenderDrawLine function for this.
	// The line starts at the center (Cx, Cy) and ends at the calculated endpoint (endX, endY).
	T_DrawLine(Cx, Cy, endX, endY);

}

void T_Graphics::Graphics::T_DrawLine(int startX, int startY, int endX, int endY)
{
	SDL_RenderLine(mainRenderer, startX, startY, endX, endY);
}

void T_Graphics::Graphics::T_DrawCirleFilled(int Cx, int Cy, int Radius)
{
	int x = 0;
	int y = Radius;
	int d = 3 - 2 * Radius;

	while (x <= y) {
		// draw horizontal spans between symmetric x points
		SDL_RenderLine(mainRenderer, Cx - x, Cy + y, Cx + x, Cy + y);
		SDL_RenderLine(mainRenderer, Cx - x, Cy - y, Cx + x, Cy - y);
		SDL_RenderLine(mainRenderer, Cx - y, Cy + x, Cx + y, Cy + x);
		SDL_RenderLine(mainRenderer, Cx - y, Cy - x, Cx + y, Cy - x);

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

void T_Graphics::Graphics::T_DrawPolygon(int x, int y, const std::vector<Vectors::Vec2D>& vertices)
{
	for (int i = 0; i < vertices.size(); i++) {
		int currIndex = i;
		int nextIndex = (i + 1) % vertices.size();
		SDL_RenderLine(mainRenderer, vertices[currIndex].xComponent, vertices[currIndex].yComponent, vertices[nextIndex].xComponent, vertices[nextIndex].yComponent);
	}
	T_DrawCirleFilled(x, y, 1);
}

void T_Graphics::Graphics::T_DrawRectangle(int xPos, int yPos, int Width, int Height)
{
	T_DrawLine(xPos - Width / 2.0f, yPos - Height / 2.0f, xPos + Width / 2.0f, yPos - Height / 2.0f);
	T_DrawLine( xPos + Width / 2.0f, yPos - Height / 2.0f, xPos + Width / 2.0f, yPos + Height / 2.0f);
	T_DrawLine( xPos + Width / 2.0f, yPos + Height / 2.0f, xPos - Width / 2.0f, yPos + Height / 2.0f);
	T_DrawLine( xPos - Width / 2.0f, yPos + Height / 2.0f, xPos - Width / 2.0f, yPos - Height / 2.0f);
}

void T_Graphics::Graphics::T_DrawRectangleFilled(int xPos, int yPos, int Width, int Height)
{

}
