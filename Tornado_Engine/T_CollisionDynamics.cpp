#include "T_CollisionDynamics.h"

bool T_CollisionDynamics::T_CollisionDetection::T_IsColliding(Body_Physics::T_Body* objectA, Body_Physics::T_Body* objectB, T_Contact& contact)
{
	bool aIsCircle = objectA->shape->GetType() == CIRCLE;
	bool bIsCircle = objectB->shape->GetType() == CIRCLE;
	bool aIsPolygon = objectA->shape->GetType() == POLYGON || objectA->shape->GetType() == BOX;
	bool bIsPolygon = objectB->shape->GetType() == POLYGON || objectB->shape->GetType() == BOX;

	if (aIsCircle && bIsCircle) {
		return T_IsCollidingCircleCircle(objectA, objectB, contact);
	}

	if (aIsPolygon && bIsPolygon) {
		return T_IsCollidingPolygonPolygon(objectA, objectB, contact);
	}

	return false;
}

bool T_CollisionDynamics::T_CollisionDetection::T_IsCollidingCircleCircle(Body_Physics::T_Body* objectA, Body_Physics::T_Body* objectB, T_Contact& contact)
{
	T_GraphicsModule::CircleShape* aCircleShape = (T_GraphicsModule::CircleShape*) objectA->shape;
	T_GraphicsModule::CircleShape* bCircleShape = (T_GraphicsModule::CircleShape*)objectB->shape;

	const Vectors::Vec2D ab = objectB->Position - objectA->Position;
	const float radiusSum = aCircleShape->Radius + bCircleShape->Radius;

	bool isColliding = ab.Vec2DMagnitudeSquared() <= (radiusSum * radiusSum);

	if(!isColliding)
		return false;

	//We Have A Collision

	contact.objectA = objectA;
	contact.objectB = objectB;

	contact._Normal = ab;
	contact._Normal.Vec2DNormalize();

	contact._Start = objectB->Position - contact._Normal * bCircleShape->Radius;
	contact._End = objectA->Position + contact._Normal * aCircleShape->Radius;
	contact._Depth = (contact._End - contact._Start).Vec2DMagnitude();

	//Compute Contact Collision Info.

	return true;
}

bool T_CollisionDynamics::T_CollisionDetection::T_IsCollidingPolygonPolygon(Body_Physics::T_Body* objectA, Body_Physics::T_Body* objectB, T_Contact& contact)
{
	//Find The Separation Between A and B & B And A.

	const T_GraphicsModule::PolygonShape* aPolygonShape = (T_GraphicsModule::PolygonShape*)objectA->shape;
	const T_GraphicsModule::PolygonShape* bPolygonShape = (T_GraphicsModule::PolygonShape*)objectB->shape;

	Vectors::Vec2D aAxis, bAxis;
	Vectors::Vec2D aPoint, bPoint;

	float abSeparation = aPolygonShape->T_FindMinimumSeparation(bPolygonShape, aAxis, aPoint);
	if (abSeparation >= 0)
		return false;
	float baSeparation = bPolygonShape->T_FindMinimumSeparation(aPolygonShape, bAxis, bPoint);
	if (baSeparation >= 0)
		return false;

	return true;
}
