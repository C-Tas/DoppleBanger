#pragma once

class Vector2D
{
private:
	double x_, y_;
public:
	Vector2D() :x_(0), y_(0) {};
	Vector2D(double x, double y) : x_(x), y_(y) {};

#pragma region Getters
	const Vector2D getVec() { return { x_,y_ }; };
	const double getX() { return x_; };
	const double getY() { return y_; };
#pragma endregion

#pragma region Setters
	void setVec(Vector2D value) { x_ = value.getX(); y_ = value.getY(); };
	void setX(double x) { x_ = x; };
	void setY(double y) { y_ = y; };
#pragma endregion

#pragma region Operators
	Vector2D operator+(const Vector2D& v)const;
	Vector2D operator-(const Vector2D& v) const;
	Vector2D operator*(double d) const;
	Vector2D operator=(const Vector2D& v)const;
#pragma endregion
};