#include "T_Body.h"

Body_Physics::T_Body::T_Body(const T_GraphicsModule::T_Shape& shape,int x, int y, float Mass)
{
	this->shape = shape.Clone();
	this->Position = Vectors::Vec2D(x, y);
	this->Velocity = Vectors::Vec2D(0.0f, 0.0f);
	this->Acceleration = Vectors::Vec2D(0.0f, 0.0f);
	this->Rotation = 0.0f;
	this->angularVelocity = 0.0f;
	this->angularAcceleration = 0.0f;
	this->NetForces = Vectors::Vec2D(0.0f, 0.0f);
	this->NetTorque = 0.0f;
	this->Mass = Mass;
	if (Mass != 0.0f) {
		this->invMass = 1.0f / Mass;
	}
	else {
		this->invMass = 0.0f;
	}
	I = shape.getMomentOfInertia() * Mass;
	if (I != 0.0f) {
		this->invI = 1.0f / I;
	}
	else {
		this->invI = 0.0f;
	}
}

Body_Physics::T_Body::~T_Body()
{
	delete shape;
}

void Body_Physics::T_Body::T_EulerIntegrateLinear(float dt)
{
	Acceleration = NetForces * invMass;
	Velocity += Acceleration * dt;
	Position += Velocity * dt;
	T_ClearForces();
}

void Body_Physics::T_Body::T_EulerIntegrateAngular(float dt) {
	angularAcceleration = NetTorque * invI;
	angularVelocity += angularAcceleration * dt;
	Rotation += angularVelocity * dt;
	T_ClearTorque();
}

void Body_Physics::T_Body::T_AddForce(const Vectors::Vec2D& force)
{
	NetForces += force;
}

void Body_Physics::T_Body::T_AddTorque(float torque) {
	NetTorque += torque;
}

void Body_Physics::T_Body::T_ClearForces()
{
	NetForces = Vectors::Vec2D(0.0f, 0.0f);
}

void Body_Physics::T_Body::T_ClearTorque() {
	NetTorque = 0.0f;
}

void Body_Physics::T_Body::T_Update(float dt)
{
	T_EulerIntegrateLinear(dt);
	T_EulerIntegrateAngular(dt);
	bool isPolygon = shape->GetType() == POLYGON || shape->GetType() == BOX;
	if (isPolygon) {
		T_GraphicsModule::PolygonShape* polygonShape = (T_GraphicsModule::PolygonShape* )shape;
		polygonShape->updateVertices(Rotation, Position);
	}
}
