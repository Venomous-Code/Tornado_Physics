#include "TParticle.h"

Particle_Physics::TParticle::TParticle(int x, int y, float Mass)
{
	this->Position = Vectors::Vec2D(x, y);
	this->Mass = Mass;
	if (Mass != 0.0f) {
		this->invMass = 1.0f / Mass;
	}
	else {
		this->invMass = 0.0f;
	}
}

Particle_Physics::TParticle::~TParticle()
{
}

void Particle_Physics::TParticle::T_EulerIntegrate(float dt)
{
	Acceleration = NetForces * invMass;
	Velocity += Acceleration * dt;
	Position += Velocity * dt;
	T_ClearForces();
}

void Particle_Physics::TParticle::T_AddForce(const Vectors::Vec2D& force)
{
	NetForces += force;
}

void Particle_Physics::TParticle::T_ClearForces()
{
	NetForces = Vectors::Vec2D(0.0f, 0.0f);
}
