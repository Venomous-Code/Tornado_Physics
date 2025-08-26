#pragma once
#include "Vectors.h"
#include <iostream>

namespace Particle_Physics {
	class TParticle
	{
	public:

		TParticle(int x, int y, float Mass);
		~TParticle();

		void T_EulerIntegrate(float dt);
		void T_AddForce(const Vectors::Vec2D& force);
		void T_ClearForces();

		Vectors::Vec2D Position;
		Vectors::Vec2D Velocity;
		Vectors::Vec2D Acceleration;
		Vectors::Vec2D NetForces;
		int Radius;

		float Mass;
		float invMass;
	private:

	};
}
