#pragma once
#include "Vectors.h"
#include "T_Body.h"

namespace T_CollisionDynamics {
	class T_Contact
	{
	public:
		Body_Physics::T_Body* objectA;
		Body_Physics::T_Body* objectB;

		Vectors::Vec2D _Start;
		Vectors::Vec2D _End;

		Vectors::Vec2D _Normal;
		float _Depth;

		T_Contact();
		~T_Contact();

		void T_ResolvePenetration();
		void T_ResolveCollision();

	private:

	};
}
