#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <math.h> 

class Vector2f
{
public:
	Vector2f();
	Vector2f(float, float);

	float length() const;
	void normalize();

	const bool operator==(const Vector2f&) const;
	const bool operator!=(const Vector2f&) const;

	Vector2f& operator+=(const Vector2f&);
	Vector2f& operator/=(const float);

	const Vector2f operator-(const Vector2f&) const;
	const Vector2f operator+(const Vector2f&) const;
	const Vector2f operator*(const Vector2f&) const;
	const Vector2f operator*(const float) const;
	const Vector2f operator*(const int) const;
	const Vector2f operator/(const int) const;

	float x = 0.0f;
	float y = 0.0f;
	float length_of_vector = 0.0f;
};

#endif // VECTOR2F_H