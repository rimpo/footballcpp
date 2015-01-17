#pragma once

#include<math.h>

#include"Vector.h"



struct Position
{
	typedef vector<Position> Vec;
	float x_;
	float y_;

	Position()
	{
		x_ = 0.0;
		y_ = 0.0;
	}
	
	Position(float x, float y)
	{
		x_ = x;
		y_ = y;
	}

	float DistanceFrom(const Position& pos) const;
	void AddVector(const Vector& vec);
	float AngleWith(const Position& pos);

	Vector VectorTo(const Position& pos) { return Vector(pos.x_ - x_, pos.y_ - y_); }

	bool ApproxEqual(const Position& pos, float tolerance) const;

	inline bool IsNegative() { return x_ < 0.0 || y_ < 0.0; }
};

