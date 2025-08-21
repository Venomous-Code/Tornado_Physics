#pragma once
#include <iostream>
#include <math.h>

namespace Vectors {
	class Vec2D
	{
	public:
		//CONSTRUCTORS
		//Constructor For Default Position (0, 0)
		Vec2D();
		//Constructor For Your Desired Position (x, y)
		Vec2D(float xComponent, float yComponent);
		//DESTRUCTORS
		~Vec2D();

		//METHODS
		void Vec2DAddition(const Vec2D& v);
		void Vec2DSubtraction(const Vec2D& v);
		void Vec2DScale(const float n);
		Vec2D Vec2DRotate(const float angle) const;

		float Vec2DMagnitude() const;
		float Vec2DMagnitudeSquared() const;

		Vec2D& Vec2DNormalize();
		Vec2D Vec2DUnitVector() const;
		Vec2D Vec2DNormal() const;

		float Vec2D_DotProduct(Vec2D& v) const;
		float Vec2D_CrossProduct(Vec2D& v) const;

		//OPERATOR OVERLOADS
		Vec2D& operator = (const Vec2D& v);
		bool operator == (const Vec2D& v) const;
		bool operator != (const Vec2D& v) const;

		Vec2D operator + (const Vec2D& v) const;
		Vec2D operator - (const Vec2D& v) const;
		Vec2D operator * (const float n) const;
		Vec2D operator / (const float n) const;
		Vec2D operator - ();

		Vec2D& operator += (const Vec2D& v);
		Vec2D& operator -= (const Vec2D& v);
		Vec2D& operator /= (const float n);
		Vec2D& operator *= (const float n);

		//DATA MEMBERS
		float xComponent;
		float yComponent;

	private:


	};
}

