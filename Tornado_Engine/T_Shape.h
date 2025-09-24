#pragma once
#include "Vectors.h"
#include <vector>
#include <iostream>

enum ShapeType {
	CIRCLE,
	POLYGON,
	BOX
};

namespace T_GraphicsModule {
	class T_Shape
	{
	public:
		virtual ~T_Shape();
		virtual ShapeType GetType() const = 0;
		virtual T_Shape* Clone() const = 0;
		virtual float getMomentOfInertia() const = 0;
	private:

	};

	class CircleShape : public T_Shape {
	public:
		float Radius;

		CircleShape(float radius);
		virtual ~CircleShape();
		ShapeType GetType() const override;
		T_Shape* Clone() const override;
		float getMomentOfInertia() const override;

	private:
	};

	class PolygonShape : public T_Shape {
	public:
		std::vector<Vectors::Vec2D> localVertices;
		std::vector<Vectors::Vec2D> globalVertices;

		PolygonShape();
		PolygonShape(const std::vector<Vectors::Vec2D> vertices);
		virtual ~PolygonShape();
		ShapeType GetType() const override;
		T_Shape* Clone() const override;
		float getMomentOfInertia() const override;
		void updateVertices(float Angle, const Vectors::Vec2D& Position);
	private:

	};

	class BoxShape : public PolygonShape {
	public:
		float width;
		float height;

		BoxShape(float width, float height);
		virtual ~BoxShape();
		ShapeType GetType() const override;
		T_Shape* Clone() const override;
		float getMomentOfInertia() const override;
	private:
	};
}