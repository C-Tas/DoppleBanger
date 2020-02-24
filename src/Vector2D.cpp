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
#pragma endregion