#pragma once
#include "T_Body.h"
#include "Vectors.h"
#include "T_Contact.h"

namespace T_CollisionDynamics {
	class T_CollisionDetection
	{
	public:
		static bool T_IsColliding(Body_Physics::T_Body* objectA, Body_Physics::T_Body* objectB, T_Contact& contact);
		static bool T_IsCollidingCircleCircle(Body_Physics::T_Body* objectA, Body_Physics::T_Body* objectB, T_Contact& contact);
		static bool T_IsCollidingPolygonPolygon(Body_Physics::T_Body* objectA, Body_Physics::T_Body* objectB, T_Contact& contact);
		//static bool T_IsCollidingPolygonCircle(Body_Physics::T_Body* objectA, Body_Physics::T_Body* objectB);
	private:
	};
}