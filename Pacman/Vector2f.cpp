#include "Vector2f.h"

Vector2f::Vector2f()
{
	x = 0.f;
	y = 0.f;
}

Vector2f::Vector2f(float x_, float y_)
{
	x = x_;
	y = y_;
}

const bool Vector2f::operator==(const Vector2f& other) const
{
	if (x == other.x && y == other.y)
	{
		return true;
	}
	return false;
}

const Vector2f Vector2f::operator-(const Vector2f& other) const
{
	Vector2f v(x - other.x, y - other.y);
	return v;
}

const Vector2f Vector2f::operator+(const Vector2f& other) const
{
	Vector2f v(x + other.x, y + other.y);
	return v;
}


const Vector2f Vector2f::operator*(const Vector2f& other) const
{
	Vector2f v(x * other.x, y * other.y);
	return v;
}

Vector2f& Vector2f::operator+=(const Vector2f& other)
{
	x = x + other.x;
	y = y + other.y;

	return *this;
}

Vector2f& Vector2f::operator*=(const float other)
{
	x *= other;
	y *= other;

	return *this;
}

Vector2f& Vector2f::operator/=(const float other)
{
	x /= other;
	y /= other;

	return *this;
}

const Vector2f Vector2f::operator*(const float other) const
{
	Vector2f v(x * other, y * other);
	return v;
}

float Vector2f::Length() const
{
	return sqrt(x * x + y * y);
}

void Vector2f::Normalize()
{
	float length = Length();

	if (length > 0.f)
	{
		*this /= length;
	}
}