#include "Vector2D.h"
#pragma region Operators
Vector2D Vector2D:: operator+(const Vector2D& v)const{
	Vector2D r;
	r.x_ = this->x_ + v.x_;
	r.y_ = this->y_ + v.y_;
	return r;
}

Vector2D Vector2D:: operator-(const Vector2D& v) const{
	Vector2D r;
	r.x_ = this->x_ - v.x_;
	r.y_ = this->y_ - v.y_;
	return r;
}
Vector2D Vector2D:: operator*(double d) const {
	Vector2D r;
	r.x_ = this->x_ *d;
	r.y_ = this->y_ *d;
	return r;
}
Vector2D Vector2D::operator=(const Vector2D& v)const {
	Vector2D r;
	r.x_ = v.x_;
	r.y_ = v.y_;
	return r;
}
bool Vector2D::operator==(const Vector2D& v) const
{
	return (x_==v.x_ && y_ ==v.y_);
}
bool Vector2D::operator!=(const Vector2D& v) const
{
	return !(x_ == v.x_ && y_ == v.y_);
}
Vector2D Vector2D::normalize() const {
	Vector2D r;
	r.x_ = x_;
	r.y_ = y_;
	double mag = magnitude();
	if (mag > 0.0) {
		r.x_ = r.x_ / mag;
		r.y_ = r.y_ / mag;
	}
	return r;
}
double Vector2D::magnitude() const
{	
	return sqrt(pow(x_, 2) + pow(y_, 2));
}
double Vector2D::angle() const
{
	return atan(y_/x_);
}
#pragma endregion