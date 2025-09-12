#pragma once
#include "Vectors.h"
#include <iostream>
#include "T_Shape.h"

namespace Body_Physics {
	class T_Body
	{
	public:
		
		T_GraphicsModule::T_Shape* shape = NULL;

		T_Body(const T_GraphicsModule::T_Shape& shape, int x, int y, float Mass);
		~T_Body();


		void T_EulerIntegrate(float dt);
		void T_AddForce(const Vectors::Vec2D& force);
		void T_ClearForces();

		Vectors::Vec2D Position;
		Vectors::Vec2D Velocity;
		Vectors::Vec2D Acceleration;
		Vectors::Vec2D NetForces;

		float Mass;
		float invMass;
	private:

	};
}
