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

	const bool operator==(const Vector2f&) const;
	const bool operator!=(const Vector2f&) const;

	Vector2f& operator+=(const Vector2f&);
	Vector2f& operator*=(const float);
	Vector2f& operator/=(const float);

	const Vector2f operator-(const Vector2f&) const;
	const Vector2f operator+(const Vector2f&) const;
	const Vector2f operator*(const Vector2f&) const;
	const Vector2f operator*(const float) const;
	const Vector2f operator*(const int) const;
	const Vector2f operator/(const int) const;

	float x;
	float y;
};

#endif // VECTOR2F_H