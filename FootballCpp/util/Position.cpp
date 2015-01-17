#include "stdafx.h"
#include "Position.h"

float Position::DistanceFrom(const Position& pos) const
{
	float diffX = (x_ - pos.x_);
	float diffY = (y_ - pos.y_);

	return sqrtf(diffX*diffX + diffY*diffY);
}

void Position::AddVector(const Vector& vec)
{
	x_ = x_ + vec.x_;
	y_ = y_ + vec.y_;
}

float Position::AngleWith(const Position& pos) 
{
	float deltaY = y_ - pos.y_;
	float deltaX = x_ - pos.x_;
	int angle = atan2f(deltaY, deltaX) * 180.0 / PI;
	angle += 270;
	angle %= 360;
	return angle;
}

bool Position::ApproxEqual(const Position& pos, float tolerance) const
{
	if (fabsf(x_ - pos.x_) <= tolerance &&
		fabsf(y_ - pos.y_) <= tolerance)
	{
		return true;
	}
	return false;
}