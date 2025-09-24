#include "T_Contact.h"

T_CollisionDynamics::T_Contact::T_Contact()
{
}

T_CollisionDynamics::T_Contact::~T_Contact()
{
}

void T_CollisionDynamics::T_Contact::T_ResolvePenetration()
{
	if (objectA->T_IsStatic() && objectB->T_IsStatic()) {
		return;
	}
	float da = _Depth / (objectA->invMass + objectB->invMass) * objectA->invMass;
	float db = _Depth / (objectA->invMass + objectB->invMass) * objectB->invMass;

	objectA->Position -= _Normal * da;
	objectB->Position += _Normal * db;
}

void T_CollisionDynamics::T_Contact::T_ResolveCollision()
{
	//Apply positional correction using the projection method
	T_ResolvePenetration();

	//Define Elasticity (Coefficient of Restitution E)
	float E = std::min(objectA->Restitution, objectB->Restitution);

	//Calculate the relative velocity between the two objects.
	const Vectors::Vec2D Vrel = (objectA->Velocity - objectB->Velocity);

	//Calculate the relative velocity along the normal collision vector.
	float VrelDotNormal = Vrel.Vec2D_DotProduct(_Normal);

	//Now we proceed to calculate the collision impulse.
	const Vectors::Vec2D impulseDirection = _Normal;
	const float impulseMagnitude = -(1 + E) * VrelDotNormal / (objectA->invMass + objectB->invMass);

	Vectors::Vec2D jn = impulseDirection * impulseMagnitude;

	//Apply the impulse vector to both objects in opposite direction
	objectA->T_ApplyImpulse(jn);
	objectB->T_ApplyImpulse(-jn);
}
