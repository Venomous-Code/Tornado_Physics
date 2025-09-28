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
	float F = std::min(objectA->friction, objectB->friction);

	//Calculate the relative velocity between the two objects.
	//const Vectors::Vec2D Vrel = (objectA->Velocity - objectB->Velocity);
	
	Vectors::Vec2D Ra = _End - objectA->Position;
	Vectors::Vec2D Rb = _Start - objectB->Position;
	Vectors::Vec2D va = objectA->Velocity + Vectors::Vec2D(-objectA->angularVelocity*Ra.yComponent, objectA->angularVelocity*Ra.xComponent);
	Vectors::Vec2D vb = objectB->Velocity + Vectors::Vec2D(-objectB->angularVelocity * Rb.yComponent, objectB->angularVelocity * Rb.xComponent);

	const Vectors::Vec2D Vrel = va - vb;

	//Calculate the relative velocity along the normal collision vector.
	float VrelDotNormal = Vrel.Vec2D_DotProduct(_Normal);

	//Now we proceed to calculate the collision impulse.
	const Vectors::Vec2D impulseDirectionN = _Normal;
	const float impulseMagnitudeN = -(1 + E) * VrelDotNormal / ((objectA->invMass + objectB->invMass) + Ra.Vec2D_CrossProduct(_Normal) * Ra.Vec2D_CrossProduct(_Normal) * objectA->invI + Rb.Vec2D_CrossProduct(_Normal) * Rb.Vec2D_CrossProduct(_Normal) * objectB->invI);

	Vectors::Vec2D jN = impulseDirectionN * impulseMagnitudeN;

	Vectors::Vec2D Tangent = _Normal.Vec2DNormal();
	float VrelDotTangent = Vrel.Vec2D_DotProduct(Tangent);
	const Vectors::Vec2D impulseDirectionT = Tangent;
	const float impulseMagnitudeT = F * -(1 + E) * VrelDotTangent / ((objectA->invMass + objectB->invMass) + Ra.Vec2D_CrossProduct(Tangent) * Ra.Vec2D_CrossProduct(Tangent) * objectA->invI + Rb.Vec2D_CrossProduct(Tangent) * Rb.Vec2D_CrossProduct(Tangent) * objectB->invI);
	
	Vectors::Vec2D jT = impulseDirectionT * impulseMagnitudeT;

	Vectors::Vec2D j = jN + jT;

	//Apply the impulse vector to both objects in opposite direction
	objectA->T_ApplyImpulse(j, Ra);
	objectB->T_ApplyImpulse(-j, Rb);
}
