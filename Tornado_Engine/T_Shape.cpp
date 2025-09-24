#include "T_Shape.h"

T_GraphicsModule::T_Shape::~T_Shape()
{
}

ShapeType T_GraphicsModule::T_Shape::GetType() const
{
    return ShapeType();
}

T_GraphicsModule::CircleShape::CircleShape(float radius)
{
    this->Radius = radius;
    std::cout << "CIRCLE SHAPE CONSTRUCTOR CALLED." << std::endl;
}

T_GraphicsModule::CircleShape::~CircleShape()
{
    std::cout << "CIRCLE SHAPE DESTRUCTOR CALLED." << std::endl;
}

ShapeType T_GraphicsModule::CircleShape::GetType() const
{
    return CIRCLE;
}

T_GraphicsModule::T_Shape* T_GraphicsModule::CircleShape::Clone() const
{
    return new CircleShape(Radius);
}

float T_GraphicsModule::CircleShape::getMomentOfInertia() const {
    //The MOI For A Circle Is 1/2 * r^2
    //But This Still Needs To Be Multiplied By The Rigid Body's Mass 
    return 0.5 * (Radius * Radius);
}

T_GraphicsModule::PolygonShape::PolygonShape()
{
}

T_GraphicsModule::PolygonShape::PolygonShape(const std::vector<Vectors::Vec2D> vertices)
{
    //TODO
}

T_GraphicsModule::PolygonShape::~PolygonShape()
{
    //TODO
}

ShapeType T_GraphicsModule::PolygonShape::GetType() const
{
    return POLYGON;
}

T_GraphicsModule::T_Shape* T_GraphicsModule::PolygonShape::Clone() const
{
    return new PolygonShape(localVertices);
}

float T_GraphicsModule::PolygonShape::getMomentOfInertia() const {
    return 0.0;
}

T_GraphicsModule::BoxShape::BoxShape(float width, float height)
{
    this->width = width;
    this->height = height;

    localVertices.push_back(Vectors::Vec2D(-width / 2.0, -height / 2.0));
    localVertices.push_back(Vectors::Vec2D(width / 2.0, -height / 2.0));
    localVertices.push_back(Vectors::Vec2D(width / 2.0, height / 2.0));
    localVertices.push_back(Vectors::Vec2D(-width / 2.0, height / 2.0));

    globalVertices.push_back(Vectors::Vec2D(-width / 2.0, -height / 2.0));
    globalVertices.push_back(Vectors::Vec2D(width / 2.0, -height / 2.0));
    globalVertices.push_back(Vectors::Vec2D(width / 2.0, height / 2.0));
    globalVertices.push_back(Vectors::Vec2D(-width / 2.0, height / 2.0));
}

T_GraphicsModule::BoxShape::~BoxShape()
{
    //TODO
}

ShapeType T_GraphicsModule::BoxShape::GetType() const
{
    return BOX;
}

T_GraphicsModule::T_Shape* T_GraphicsModule::BoxShape::Clone() const
{
    return new BoxShape(width, height);
}

float T_GraphicsModule::BoxShape::getMomentOfInertia() const {
    //For A Rectangle, The MOI Is 1/12 * (w^2 + h^2)
    //But This Still Needs To Be Multiplied By The Rigid Body's Mass.
    return (0.083333) * (width * width + height * height);
}

void T_GraphicsModule::PolygonShape::updateVertices(float Angle, const Vectors::Vec2D& Position) {
    for (int i = 0; i < localVertices.size(); i++) {
        globalVertices[i] = localVertices[i].Vec2DRotate(Angle);
        globalVertices[i] += Position;
    }
}