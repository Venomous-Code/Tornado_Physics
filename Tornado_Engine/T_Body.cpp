#include "T_Body.h"

Body_Physics::T_Body::T_Body(const T_GraphicsModule::T_Shape& shape,int x, int y, float Mass)
{
	this->shape = shape.Clone();
	this->Position = Vectors::Vec2D(x, y);
	this->Mass = Mass;
	if (Mass != 0.0f) {
		this->invMass = 1.0f / Mass;
	}
	else {
		this->invMass = 0.0f;
	}
}

Body_Physics::T_Body::~T_Body()
{
	delete shape;
}

void Body_Physics::T_Body::T_EulerIntegrate(float dt)
{
	Acceleration = NetForces * invMass;
	Velocity += Acceleration * dt;
	Position += Velocity * dt;
	T_ClearForces();
}

void Body_Physics::T_Body::T_AddForce(const Vectors::Vec2D& force)
{
	NetForces += force;
}

void Body_Physics::T_Body::T_ClearForces()
{
	NetForces = Vectors::Vec2D(0.0f, 0.0f);
}
