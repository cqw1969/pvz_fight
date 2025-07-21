#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <cmath>
class Vector2
{
public:
	float x = 0;
	float y = 0;

	Vector2()=default;
	~Vector2()=default;
	Vector2(float x, float y) : x(x), y(y) {}

	Vector2 operator+(const Vector2& vec) const;
	void operator+=(const Vector2& vec);
	void operator -=(const Vector2& vec);
	Vector2 operator-(const Vector2& vec) const;
	float operator*(const Vector2& vec) const;//dot product
	Vector2 operator*(float val) const;//scalar multiplication
	void operator*=(float val);
	float length();
	Vector2 normalize();
};


#endif // !_VECTOR2_H_