#include "T_Sandbox.h"
#include "Constants.h"
#include "T_Shape.h"

Tornado_Engine::Sandbox::Sandbox()
{
	vec2 = new Vectors::Vec2D(10, 25);
	GFX = new T_Graphics::Graphics;
	/*SmallBall = new Body_Physics::T_Body(150, 125, 1.0f);
	SmallBall->Radius = 4;
	bodies.push_back(SmallBall);
	BigBall = new Body_Physics::T_Body(200, 135, 20.0f);
	BigBall->Radius = 20;
	bodies.push_back(BigBall);*/
	//mouseCursor = new Vectors::Vec2D(0.0f, 0.0f);

	//Anchor = Vectors::Vec2D(200.0f, 30.0f);
	//Body_Physics::T_Body* Box = new Body_Physics::T_Body(T_GraphicsModule::BoxShape(200,100), (GFX->T_GetWidth()/2.0f), (GFX->T_GetHeight()/2.0f), 2.0f);

	int xPosition = WINDOWWIDTH / 2;
	int yPosition = WINDOWHEIGHT / 2;

	//Body_Physics::T_Body* Bigball = new Body_Physics::T_Body(T_GraphicsModule::CircleShape(200), WINDOWWIDTH/2.0, WINDOWHEIGHT/2.0, 0.0);

	Body_Physics::T_Body* BoxA = new Body_Physics::T_Body(T_GraphicsModule::BoxShape(200, 200), WINDOWWIDTH / 2.0, WINDOWHEIGHT / 2.0, 0.0);

	Body_Physics::T_Body* Floor = new Body_Physics::T_Body(T_GraphicsModule::BoxShape(1300, 50), 700, 800, 0.0);
	Body_Physics::T_Body* RightWall = new Body_Physics::T_Body(T_GraphicsModule::BoxShape(50, 600), 1325, 475, 0.0);
	Body_Physics::T_Body* LeftWall = new Body_Physics::T_Body(T_GraphicsModule::BoxShape(50, 600), 75, 475, 0.0);
	
	//Body_Physics::T_Body* BoxB = new Body_Physics::T_Body(T_GraphicsModule::BoxShape(200, 200), WINDOWWIDTH / 2.0, WINDOWHEIGHT / 2.0, 1.0);

	BoxA->angularVelocity = 0.4f;
	//BoxB->angularVelocity = 0.1f;
	BoxA->Rotation = 1.4f;
	BoxA->Restitution = 0.7f;
	Floor->Restitution = 0.7f;
	LeftWall->Restitution = 0.7f;
	RightWall->Restitution = 0.7f;
	//Bigball->Rotation = 1.4f;
	//Bigball->Restitution = 0.3f;

	bodies.push_back(BoxA);
	//bodies.push_back(BoxB);
	bodies.push_back(Floor);
	bodies.push_back(RightWall);
	bodies.push_back(LeftWall);


	//Body_Physics::T_Body* Smallball = new Body_Physics::T_Body(T_GraphicsModule::CircleShape(50), 100, 50, 1.0);

	//Body_Physics::T_Body* Bob = new Body_Physics::T_Body(T_GraphicsModule::CircleShape(50.0f), xPosition, yPosition, 2.0f);

	//bodies.push_back(Bigball);
	//bodies.push_back(Smallball); 

	/*Fluid.x = 720;
	Fluid.y = 667;
	Fluid.w = 1440;
	Fluid.h = 400;*/
}

Tornado_Engine::Sandbox::~Sandbox()
{
	//DELETE THE INSTANCES OVER HERE.
	delete vec2;
	delete GFX;
	for (auto body : bodies) {
		delete body;
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
				if (event.key.key == SDLK_D)
					Debug = !Debug;
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
			/*case SDL_EVENT_MOUSE_MOTION:
				float cursorX, cursorY;
				SDL_GetMouseState(&cursorX, &cursorY);
				bodies[1]->Position.xComponent = cursorX;
				bodies[1]->Position.yComponent = cursorY;
				break;*/
			/*case SDL_EVENT_MOUSE_MOTION:
				mouseCursor.xComponent = event.motion.x;
				mouseCursor.yComponent = event.motion.y;
				break;*/
			/*case SDL_EVENT_MOUSE_BUTTON_DOWN:
				if (!LeftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT) {
					LeftMouseButtonDown = true;
					float xCursorPos, yCursorPos;
					SDL_GetMouseState(&xCursorPos, &yCursorPos);
					mouseCursor.xComponent = xCursorPos;
					mouseCursor.yComponent = yCursorPos;
				}
				break;*/
			/*case SDL_EVENT_MOUSE_BUTTON_DOWN:
				float xPos, yPos;
				SDL_GetMouseState(&xPos, &yPos);
				Body_Physics::T_Body* smallBox = new Body_Physics::T_Body(T_GraphicsModule::BoxShape(80, 80), xPos, yPos, 1.0);
				smallBox->Restitution = 0.1f;
				bodies.push_back(smallBox);
				break;*/
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				float xPos, yPos;
				SDL_GetMouseState(&xPos, &yPos);

				std::vector<Vectors::Vec2D> vertices = { Vectors::Vec2D(20,60), Vectors::Vec2D(-40,20), Vectors::Vec2D(-20,-60), Vectors::Vec2D(20,-60), Vectors::Vec2D(40,20) };

				Body_Physics::T_Body* Poly = new Body_Physics::T_Body(T_GraphicsModule::PolygonShape(vertices), xPos, yPos, 2.0);
				Poly->Restitution = 0.01f;
				//For Others Shapes Try: Restitution = 0.1 & friction = 0.7
				Poly->friction = 0.3f;
				bodies.push_back(Poly);
				break;
			/*case SDL_EVENT_MOUSE_BUTTON_UP:
				if (LeftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT) {
					LeftMouseButtonDown = false;
					Vectors::Vec2D ImpulseDirection = (bodies[0]->Position - mouseCursor).Vec2DUnitVector();
					float impulseMagnitude = (bodies[0]->Position - mouseCursor).Vec2DMagnitude() * 5.0f;
					bodies[0]->Velocity = ImpulseDirection * impulseMagnitude;
				}
				break;*/
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

		//Drawing Code Here Like This:
		//draw.T_DrawCirleFilled(renderer, body->Position.xComponent, body->Position.yComponent, 5);
	
	//DRAW LINE
	/*GFX->T_DrawLine(Anchor.xComponent, Anchor.yComponent, bodies[0]->Position.xComponent, bodies[0]->Position.yComponent);*/
	//DRAW ANCHOR
	//GFX->T_DrawCirleFilled(Anchor.xComponent, Anchor.yComponent, 5);
	//DRAW Bob
	for(auto body:bodies){

		if (body->shape->GetType() == CIRCLE) {
			T_GraphicsModule::CircleShape* circleShape = (T_GraphicsModule::CircleShape*)body->shape;
			GFX->T_DrawCircle(body->Position.xComponent, body->Position.yComponent, circleShape->Radius, body->Rotation);
			/*RotationAngle += 15.0f;*/
		}
		if (body->shape->GetType() == BOX) {
			T_GraphicsModule::BoxShape* boxShape = (T_GraphicsModule::BoxShape*)body->shape;
			GFX->T_DrawPolygon(body->Position.xComponent, body->Position.yComponent, boxShape->globalVertices);
		}
		if (body->shape->GetType() == POLYGON) {
			T_GraphicsModule::PolygonShape* polygonShape = (T_GraphicsModule::PolygonShape*)body->shape;
			GFX->T_DrawPolygon(body->Position.xComponent, body->Position.yComponent, polygonShape->globalVertices);
		}
	}

	/*GFX->T_DrawCirleFilled(bodies[0]->Position.xComponent, bodies[0]->Position.yComponent, bodies[0]->Radius);
	GFX->T_DrawCirleFilled(bodies[1]->Position.xComponent, bodies[1]->Position.yComponent, bodies[1]->Radius);*/

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	/*GFX->T_DrawRectangle(720, 667, 1440, 400);*/
	//							435							720
	//GFX->T_DrawRectangle(Fluid.x, Fluid.y , Fluid.w, Fluid.h);

	//PHYSICS UPDATES
	T_UpdatePhysics();

	SDL_RenderPresent(renderer);
}

void Tornado_Engine::Sandbox::T_Update()
{
	// ANY ONETIME COMMAND CAN BE TYPED HERE.
	GFX->T_GraphicsInit("TORNADO_ENGINE", WINDOWWIDTH, WINDOWHEIGHT, SDL_WINDOW_MAXIMIZED);
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
	/*body->Position.xComponent += body->Velocity.xComponent;
	body->Position.yComponent += body->Velocity.yComponent;
									OR 
	body->Position.Vec2DAddition(body->Velocity);
									OR
	body->Position += body->Velocity * deltaTime;
									*/
	//ADD FORCES
	for (auto body : bodies) {
		//Apply Wind Force
		//Vectors::Vec2D wind = Vectors::Vec2D(0.2f * PIXELS_PER_METER, 0.0f);
		//body->T_AddForce(wind);
		//Apply Weight Force
		Vectors::Vec2D weight = Vectors::Vec2D(0.0f, body->Mass * 9.8f * PIXELS_PER_METER);
		body->T_AddForce(weight);
		//Apply Push Force
		body->T_AddForce(PushForce);

		//Generate Drag Force
		/*if (body->Position.yComponent >= Fluid.y) {*/
		//Vectors::Vec2D drag = T_Physics::T_Force::T_GenerateDragForce(*body, 0.001f);
		//body->T_AddForce(drag);

			//Generate Friction Force
		//Vectors::Vec2D Friction = T_Physics::T_Force::T_GenerateFrictionForce(*body, 3.0f * PIXELS_PER_METER);
		//body->T_AddForce(Friction);
		//}

		//Add Torque Force
		/*float Torque = 20 * PI;
		body->T_AddTorque(Torque);*/


		// Generate Gravitational Attraction Force
		/*Vectors::Vec2D Attraction = T_Physics::T_Force::T_GenerateGravitationalForce(*bodies[0], *bodies[1], 1000.0f, 5.0f, 100.0f);
		bodies[0]->T_AddForce(Attraction);
		bodies[1]->T_AddForce(-Attraction);*/

		/*Vectors::Vec2D SpringForce = T_Physics::T_Force::T_GenerateSpringForce(*bodies[0], Anchor, RestLength, K);
		bodies[0]->T_AddForce(SpringForce);*/



		//HERE THE ACCELERATION IS 9.8 WHICH IS ACTUALLY THE CHANGE IN VELOCITY PER SECOND OR UNIT TIME, SO, HERE IN EACH FRAME WE ARE ACTUALLY UPDATING OUR VELOCITY BASED ON ACCELERATION.
		for (auto body : bodies) {
			/*body->T_EulerIntegrateLinear(deltaTime);
			body->T_EulerIntegrateAngular(deltaTime);
			bool isPolygon = body->shape->GetType() == POLYGON || body->shape->GetType() == BOX;
			if (isPolygon) {
				T_GraphicsModule::PolygonShape* polygonShape = (T_GraphicsModule::PolygonShape* )body->shape;
				polygonShape->updateVertices(body->Rotation, body->Position);
			}*/

			body->T_Update(deltaTime);

		}

		//Check All Rigid Bodies With Other Rigid Bodies For Collision 
		for (int i = 0; i < bodies.size() - 1; i++) {
			for (int j = 0; j < bodies.size(); j++) {
				//TODO... Check Bodies [i] With Bodies [j]
				Body_Physics::T_Body* objectA = bodies[i];
				Body_Physics::T_Body* objectB = bodies[j];

				objectA->isColliding = false;
				objectB->isColliding = false;
				T_CollisionDynamics::T_Contact contact;
				if (T_CollisionDynamics::T_CollisionDetection::T_IsColliding(objectA, objectB, contact)) {
					//Resolve The Collision Using Impulse Method.
					contact.T_ResolveCollision();

					if (Debug) {
						//Here we have the Contact info inside the contact object...
						GFX->T_DrawCirleFilled(contact._Start.xComponent, contact._Start.yComponent, 3);
						GFX->T_DrawCirleFilled(contact._End.xComponent, contact._End.yComponent, 3);
						GFX->T_DrawLine(contact._Start.xComponent, contact._Start.yComponent, contact._Start.xComponent + contact._Normal.xComponent * 15, contact._Start.yComponent + contact._Normal.yComponent * 15);

						objectA->isColliding = true;
						objectB->isColliding = true;
					}
				}
			}
		}


		for (auto body : bodies) {
			//BOUND THE PARTICLE INSIDE THE WINDOW
			if (body->shape->GetType() == CIRCLE) {
				T_GraphicsModule::CircleShape* circleShape = (T_GraphicsModule::CircleShape*) body->shape;
				if (body->Position.xComponent - circleShape->Radius <= 0) {
					body->Position.xComponent = circleShape->Radius;
					body->Velocity.xComponent *= -0.7f;
				}
				else if (body->Position.xComponent + circleShape->Radius >= WINDOWWIDTH) {
					body->Position.xComponent = WINDOWWIDTH - circleShape->Radius;
					body->Velocity *= -0.7f;
				}

				if (body->Position.yComponent - circleShape->Radius <= 0) {
					body->Position.yComponent = circleShape->Radius;
					body->Velocity.yComponent *= -0.7f;
				}
				else if (body->Position.yComponent + circleShape->Radius >= WINDOWHEIGHT) {
					body->Position.yComponent = WINDOWHEIGHT - circleShape->Radius;
					body->Velocity.yComponent *= -0.7f;
				}
			}
		}
	}
}


void Tornado_Engine::Sandbox::T_OneTimePhysicsSetup() {
	//ONE TIME PHYSICS UPDATES
	//body->Velocity = Vectors::Vec2D(0.0f, 0.0f);
	//body->Acceleration = Vectors::Vec2D(0.0f, 0.0f);
	PushForce = Vectors::Vec2D(0.0f, 0.0f);
}
