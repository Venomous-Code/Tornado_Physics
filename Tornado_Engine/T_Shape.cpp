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
    return new PolygonShape(vertices);
}

T_GraphicsModule::BoxShape::BoxShape(float width, float height)
{
    //TODO
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
