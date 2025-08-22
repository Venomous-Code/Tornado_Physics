#include "TParticle.h"

Particle_Physics::TParticle::TParticle(int x, int y, float Mass)
{
	this->Position = Vectors::Vec2D(x, y);
	this->Mass = Mass;
}

Particle_Physics::TParticle::~TParticle()
{
}
