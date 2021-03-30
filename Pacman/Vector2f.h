#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <math.h> 

class Vector2f
{
public:
	Vector2f();
	Vector2f(float, float);

	float Length() const;
	void Normalize();

	const bool operator==(const Vector2f& other) const;

	Vector2f& operator+=(const Vector2f& other);
	Vector2f& operator*=(const float aFloat);
	Vector2f& operator/=(const float aFloat);

	const Vector2f operator*(const float aValue) const;
	const Vector2f operator-(const Vector2f& other) const;
	const Vector2f operator+(const Vector2f& other) const;
	const Vector2f operator*(const Vector2f& other) const;

	float x;
	float y;
};

#endif // VECTOR2F_H