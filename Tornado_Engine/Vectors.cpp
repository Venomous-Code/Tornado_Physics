#include "Vectors.h"

Vectors::Vec2D::Vec2D()
	: xComponent(0.0f), yComponent(0.0f)
{

}

Vectors::Vec2D::Vec2D(float xComponent, float yComponent)
	: xComponent(xComponent), yComponent(yComponent)
{

}

Vectors::Vec2D::~Vec2D() {}

void Vectors::Vec2D::Vec2DAddition(const Vec2D& v)
{
	xComponent += v.xComponent;
	yComponent += v.yComponent;
}

void Vectors::Vec2D::Vec2DSubtraction(const Vec2D& v)
{
	xComponent -= v.xComponent;
	yComponent -= v.yComponent;
}

void Vectors::Vec2D::Vec2DScale(const float n)
{
	xComponent *= n;
	yComponent *= n;
}

Vectors::Vec2D Vectors::Vec2D::Vec2DRotate(const float angle) const
{
	Vec2D result;
	result.xComponent = xComponent * cos(angle) - yComponent * sin(angle);
	result.yComponent = xComponent * sin(angle) + yComponent * cos(angle);
	return result;
}

float Vectors::Vec2D::Vec2DMagnitude() const
{
	return sqrtf(xComponent * xComponent + yComponent * yComponent);
}

float Vectors::Vec2D::Vec2DMagnitudeSquared() const
{
	return (xComponent * xComponent + yComponent * yComponent);
}

Vectors::Vec2D& Vectors::Vec2D::Vec2DNormalize()
{
	float Len = Vec2DMagnitude();
	if (Len != 0.0f) {
		xComponent /= Len;
		yComponent /= Len;
	}
	return *this;
}

Vectors::Vec2D Vectors::Vec2D::Vec2DUnitVector() const
{
	Vec2D result = Vec2D(0.0f, 0.0f);
	float Len = Vec2DMagnitude();
	if (Len != 0.0f) {
		result.xComponent = xComponent / Len;
		result.yComponent = yComponent / Len;
	}
	return result;
}

Vectors::Vec2D Vectors::Vec2D::Vec2DNormal() const
{
	return Vec2D(yComponent, -xComponent).Vec2DNormalize();
}

float Vectors::Vec2D::Vec2D_DotProduct(Vec2D& v) const
{
	return (xComponent * v.xComponent) + (yComponent * v.yComponent);
}

float Vectors::Vec2D::Vec2D_CrossProduct(Vec2D& v) const
{
	return (xComponent * v.yComponent) - (yComponent * v.xComponent);
}


//OPERATOR OVERLOADING 
Vectors::Vec2D& Vectors::Vec2D::operator=(const Vec2D& v)
{
	xComponent = v.xComponent;
	yComponent = v.yComponent;
	return *this;
}

bool Vectors::Vec2D::operator==(const Vec2D& v) const
{
	return xComponent == v.xComponent && yComponent == v.yComponent;
}

bool Vectors::Vec2D::operator!=(const Vec2D& v) const
{
	return !(*this == v);
}

Vectors::Vec2D Vectors::Vec2D::operator+(const Vec2D& v) const
{
	Vec2D Result;
	Result.xComponent = xComponent + v.xComponent;
	Result.yComponent = yComponent + v.yComponent;
	return Result;
}

Vectors::Vec2D Vectors::Vec2D::operator-(const Vec2D& v) const
{
	Vec2D Result;
	Result.xComponent = xComponent - v.xComponent;
	Result.yComponent = yComponent - v.yComponent;
	return Result;
}

Vectors::Vec2D Vectors::Vec2D::operator*(const float n) const
{
	Vec2D Result;
	Result.xComponent = xComponent * n;
	Result.yComponent = yComponent * n;
	return Result;
}

Vectors::Vec2D Vectors::Vec2D::operator/(const float n) const
{
	Vec2D Result;
	Result.xComponent = xComponent / n;
	Result.yComponent = yComponent / n;
	return Result;
}

Vectors::Vec2D Vectors::Vec2D::operator-()
{
	Vec2D Result;
	Result.xComponent = xComponent * -1;
	Result.yComponent = yComponent * -1;
	return Result;
}

Vectors::Vec2D& Vectors::Vec2D::operator+=(const Vec2D& v)
{
	xComponent += v.xComponent;
	yComponent += v.yComponent;
	return *this;
}

Vectors::Vec2D& Vectors::Vec2D::operator-=(const Vec2D& v)
{
	xComponent -= v.xComponent;
	yComponent -= v.yComponent;
	return *this;
}

Vectors::Vec2D& Vectors::Vec2D::operator/=(const float n)
{
	xComponent /= n;
	yComponent /= n;
	return *this;
}

Vectors::Vec2D& Vectors::Vec2D::operator*=(const float n)
{
	xComponent *= n;
	yComponent *= n;
	return *this;
}
