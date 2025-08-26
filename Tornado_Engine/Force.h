#pragma once
#include "Vectors.h"
#include "TParticle.h"

namespace T_Physics {
	class T_Force
	{
	public:
		static Vectors::Vec2D T_GenerateDragForce(const Particle_Physics::TParticle& particle, float K);
	private:

	};
}
