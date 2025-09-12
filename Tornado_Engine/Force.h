#pragma once
#include "Vectors.h"
#include "T_Body.h"
#include <algorithm>

namespace T_Physics {
	class T_Force
	{
	public:
		static Vectors::Vec2D T_GenerateDragForce(const Body_Physics::T_Body& body, float K);
		static Vectors::Vec2D T_GenerateFrictionForce(const Body_Physics::T_Body& body, float K);
		static Vectors::Vec2D T_GenerateGravitationalForce(const Body_Physics::T_Body& a, const Body_Physics::T_Body& b, float G, float minDistance, float maxDistance);
		static Vectors::Vec2D T_GenerateSpringForce(const Body_Physics::T_Body& body, Vectors::Vec2D Anchor, float restLength, float K);
	private:

	};
}
