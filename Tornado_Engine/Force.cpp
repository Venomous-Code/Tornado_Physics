#include "Force.h"

Vectors::Vec2D T_Physics::T_Force::T_GenerateDragForce(const Body_Physics::T_Body& body, float K)
{
    Vectors::Vec2D DragForce = Vectors::Vec2D(0.0f, 0.0f);

    if (body.Velocity.Vec2DMagnitudeSquared() > 0) {
        Vectors::Vec2D DragDirection = body.Velocity.Vec2DUnitVector() * -1.0f;
        float DragMagnitude = K * body.Velocity.Vec2DMagnitudeSquared();
        DragForce = DragDirection * DragMagnitude;
    }

    return DragForce;
}

Vectors::Vec2D T_Physics::T_Force::T_GenerateFrictionForce(const Body_Physics::T_Body& body, float K)
{
    Vectors::Vec2D FrictionForce = Vectors::Vec2D(0.0f, 0.0f);
    Vectors::Vec2D FrictionDirection = body.Velocity.Vec2DUnitVector() * -1.0f;
    float FrictionMagnitude = K;
    FrictionForce = FrictionDirection * FrictionMagnitude;
    return FrictionForce;
}

Vectors::Vec2D T_Physics::T_Force::T_GenerateGravitationalForce(const Body_Physics::T_Body& a, const Body_Physics::T_Body& b, float G, float minDistance, float maxDistance)
{
    Vectors::Vec2D d = (b.Position - a.Position);

    float distanceSquared = d.Vec2DMagnitudeSquared();
    distanceSquared = std::clamp(distanceSquared, minDistance, maxDistance);
    Vectors::Vec2D AttractionDirection = d.Vec2DUnitVector();
    float AttractionMagnitude = G * (a.Mass * b.Mass) / distanceSquared;
    Vectors::Vec2D AttractionForce = AttractionDirection * AttractionMagnitude;

    return AttractionForce;
}

Vectors::Vec2D T_Physics::T_Force::T_GenerateSpringForce(const Body_Physics::T_Body& body, Vectors::Vec2D Anchor, float restLength, float K)
{
    Vectors::Vec2D d = body.Position - Anchor;

    // Find the spring displacement considering the rest length
    float Displacement = d.Vec2DMagnitude() - restLength;

    // Calculate the direction of the spring force
    Vectors::Vec2D springDirection = d.Vec2DUnitVector();

    // Calculate the magnitude of the spring force
    float springMagnitude = -K * Displacement;

    // Calculate the final resulting spring force vector
    Vectors::Vec2D springForce = springDirection * springMagnitude;
    return springForce;
}
