#pragma once
#include "Vectors.h"
#include <iostream>
#include "T_Shape.h"

namespace Body_Physics {
	class T_Body
	{
	public:
		
		T_GraphicsModule::T_Shape* shape = nullptr;

		T_Body(const T_GraphicsModule::T_Shape& shape, int x, int y, float Mass);
		~T_Body();


		void T_EulerIntegrateLinear(float dt);
		void T_EulerIntegrateAngular(float dt);
		void T_AddForce(const Vectors::Vec2D& force);
		void T_AddTorque(float torque);
		void T_ClearForces();
		void T_ClearTorque();
		void T_Update(float dt);

		//Linear Transformations
		Vectors::Vec2D Position;
		Vectors::Vec2D Velocity;
		Vectors::Vec2D Acceleration;		
		
		//Angular Transformations
		float Rotation;
		float angularVelocity;
		float angularAcceleration;

		//Forces & Torque
		Vectors::Vec2D NetForces;
		float NetTorque;
		
		// Mass & Moment of Inertia
		float Mass;
		float invMass;
		float I;
		float invI;
		
		bool isColliding = false;

	private:

	};
}
