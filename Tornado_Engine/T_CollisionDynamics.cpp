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

	if (aIsCircle && bIsPolygon) {
		return T_IsCollidingPolygonCircle(objectB, objectA, contact);
	}

	if (aIsPolygon && bIsCircle) {
		return T_IsCollidingPolygonCircle(objectA, objectB, contact);
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

	//Populate The Contact Information Values
	contact.objectA = objectA;
	contact.objectB = objectB;

	if (abSeparation > baSeparation) {
		contact._Depth = -abSeparation;
		contact._Normal = aAxis.Vec2DNormal();
		contact._Start = aPoint;
		contact._End = aPoint + contact._Normal * contact._Depth;
	}
	else {
		contact._Depth = -baSeparation;
		contact._Normal = -bAxis.Vec2DNormal();
		contact._Start = bPoint - contact._Normal * contact._Depth;
		contact._End = bPoint;
	}

	return true;
}

bool T_CollisionDynamics::T_CollisionDetection::T_IsCollidingPolygonCircle(Body_Physics::T_Body* Polygon, Body_Physics::T_Body* Circle, T_Contact& contact)
{
	
	const T_GraphicsModule::PolygonShape* polygonshape = (T_GraphicsModule::PolygonShape*)Polygon->shape;
	const T_GraphicsModule::CircleShape* circleshape = (T_GraphicsModule::CircleShape*)Circle->shape;
	const std::vector<Vectors::Vec2D>& polygonVertices = polygonshape->globalVertices;

	bool isOutside = false;
	Vectors::Vec2D minCurrVertex;
	Vectors::Vec2D minNextVertex;
	float distanceCircleEdge = std::numeric_limits<float>::lowest();

	for (int i = 0; i < polygonVertices.size(); i++) {
		int currVertex = i;
		int nextVertex = (i + 1) % polygonVertices.size();
		Vectors::Vec2D Edge = polygonshape->EdgeAt(currVertex);
		Vectors::Vec2D Normal = Edge.Vec2DNormal();

		Vectors::Vec2D vertexToCircleCenter = Circle->Position - polygonVertices[currVertex];

		float projection = vertexToCircleCenter.Vec2D_DotProduct(Normal);

		if (projection > 0) {
			distanceCircleEdge = projection;
			minCurrVertex = polygonshape->globalVertices[currVertex];
			minNextVertex = polygonshape->globalVertices[nextVertex];
			isOutside = true;
			break;
		}
		else {
			if (projection > distanceCircleEdge) {
				distanceCircleEdge = projection;
				minCurrVertex = polygonVertices[currVertex];
				minNextVertex = polygonVertices[nextVertex];
			}
		}
	}

	if (isOutside) {
		Vectors::Vec2D v1 = Circle->Position - minCurrVertex;
		Vectors::Vec2D v2 = minNextVertex - minCurrVertex;
		if (v1.Vec2D_DotProduct(v2) < 0) {
			if (v1.Vec2DMagnitude() > circleshape->Radius) {
				return false;
			}
			else {
				contact.objectA = Polygon;
				contact.objectB = Circle;
				contact._Depth = circleshape->Radius - v1.Vec2DMagnitude();
				contact._Normal = v1.Vec2DNormalize();
				contact._Start = Circle->Position + (contact._Normal * -circleshape->Radius);
				contact._End = contact._Start + (contact._Normal * contact._Depth);
			}
		}
		else {
			v1 = Circle->Position - minNextVertex;
			v2 = minCurrVertex - minNextVertex;
			if (v1.Vec2D_DotProduct(v2) < 0) {
				if (v1.Vec2DMagnitude() > circleshape->Radius) {
					return false;
				}
				else {
					contact.objectA = Polygon;
					contact.objectB = Circle;
					contact._Depth = circleshape->Radius - v1.Vec2DMagnitude();
					contact._Normal = v1.Vec2DNormalize();
					contact._Start = Circle->Position + (contact._Normal * -circleshape->Radius);
					contact._End = contact._Start + (contact._Normal * contact._Depth);
				}
			}
			else {
				if (distanceCircleEdge > circleshape->Radius) {
					return false;
				}
				else {
					contact.objectA = Polygon;
					contact.objectB = Circle;
					contact._Depth = circleshape->Radius - distanceCircleEdge;
					contact._Normal = (minNextVertex - minCurrVertex).Vec2DNormal();
					contact._Start = Circle->Position - (contact._Normal * circleshape->Radius);
					contact._End = contact._Start + (contact._Normal * contact._Depth);
				}
			}
		}
	}
	else {
		contact.objectA = Polygon;
		contact.objectB = Circle;
		contact._Depth = circleshape->Radius - distanceCircleEdge;
		contact._Normal = (minNextVertex - minCurrVertex).Vec2DNormal();
		contact._Start = Circle->Position - (contact._Normal * circleshape->Radius);
		contact._End = contact._Start + (contact._Normal * contact._Depth);
	}

	return true;

}

