#include "Vector2f.h"

//create a vector with default of x = 0, y = 0
Vector2f::Vector2f()
{
	x = 0.0f;
	y = 0.0f;
	length = 0.0f;
}

//create a vector with passed variables
Vector2f::Vector2f(float x_, float y_)
{
	x = x_;
	y = y_;
}

//compare two vectors to check if they are equal
const bool Vector2f::operator==(const Vector2f& other) const
{
	if (x == other.x && y == other.y)
	{
		return true;
	}
	return false;
}

//compare two vectors to check if they are not equal
const bool Vector2f::operator!=(const Vector2f& other) const
{
	if (x != other.x && y != other.y)
	{
		return true;
	}
	return false;
}

//subtract one vector from the other
const Vector2f Vector2f::operator-(const Vector2f& other) const
{
	Vector2f v(x - other.x, y - other.y);
	return v;
}

//add one vector to the other
const Vector2f Vector2f::operator+(const Vector2f& other) const
{
	Vector2f v(x + other.x, y + other.y);
	return v;
}

//multiple one vector with the other
const Vector2f Vector2f::operator*(const Vector2f& other) const
{
	Vector2f v(x * other.x, y * other.y);
	return v;
}

//add a vector to the current value of a vector i.e 1 += 2 == 3
Vector2f& Vector2f::operator+=(const Vector2f& other)
{
	x = x + other.x;
	y = y + other.y;

	return *this;
}

//devide a vectors current value from a float
Vector2f& Vector2f::operator/=(const float other)
{
	x /= other;
	y /= other;

	return *this;
}

//multiply a vector by a float
const Vector2f Vector2f::operator*(const float other) const
{
	Vector2f v(x * other, y * other);
	return v;
}

//multiply a vector by an int
const Vector2f Vector2f::operator*(const int other) const
{
	Vector2f v(x * other, y * other);
	return v;
}


//devide a vector by an int
const Vector2f Vector2f::operator/(const int other) const
{
	Vector2f v(x / other, y / other);
	return v;
}

//get the length of a vector
float Vector2f::Length() const
{
	return sqrt(x * x + y * y);
}

//normalize a vector
void Vector2f::Normalize()
{
	length = Length();

	if (length > 0.f)
	{
		*this /= length;
	}
}