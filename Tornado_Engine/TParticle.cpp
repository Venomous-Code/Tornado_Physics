#include "TParticle.h"

Particle_Physics::TParticle::TParticle(int x, int y, float Mass)
{
	this->Position = Vectors::Vec2D(x, y);
	this->Mass = Mass;
	std::cout << "Particle Contructor Called!!!" << std::endl;
}

Particle_Physics::TParticle::~TParticle()
{
	std::cout << "Particle Destructor Called!!!" << std::endl;
}
