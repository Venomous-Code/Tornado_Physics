#pragma once
#include "Vectors.h"
#include <iostream>

namespace Particle_Physics {
	class TParticle
	{
	public:

		TParticle(int x, int y, float Mass);
		~TParticle();

		Vectors::Vec2D Position;
		Vectors::Vec2D Velocity;
		Vectors::Vec2D Acceleration;

		float Mass;
	private:

	};
}
