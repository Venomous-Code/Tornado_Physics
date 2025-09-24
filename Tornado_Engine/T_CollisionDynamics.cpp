#include "T_CollisionDynamics.h"

bool T_CollisionDynamics::T_CollisionDetection::T_IsColliding(Body_Physics::T_Body* objectA, Body_Physics::T_Body* objectB)
{
	bool aIsCircle = objectA->shape->GetType() == CIRCLE;
	bool bIsCircle = objectB->shape->GetType() == CIRCLE;

	if (aIsCircle && bIsCircle) {
		return T_IsCollidingCircleCircle(objectA, objectB);
	}
}

bool T_CollisionDynamics::T_CollisionDetection::T_IsCollidingCircleCircle(Body_Physics::T_Body* objectA, Body_Physics::T_Body* objectB)
{
	T_GraphicsModule::CircleShape* aCircleShape = (T_GraphicsModule::CircleShape*) objectA->shape;
	T_GraphicsModule::CircleShape* bCircleShape = (T_GraphicsModule::CircleShape*)objectB->shape;

	const Vectors::Vec2D ab = objectB->Position - objectA->Position;
	const float radiusSum = aCircleShape->Radius + bCircleShape->Radius;

	bool isColliding = ab.Vec2DMagnitudeSquared() <= (radiusSum * radiusSum);

	return isColliding;
}
