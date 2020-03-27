#pragma once

#include "SDL_assert.h"
#include <iostream>
#include <math.h>

// Número PI. Necesario en Visual Studio
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

class Vector2D
{
private:
	double x_, y_;
public:
	Vector2D() :x_(0), y_(0) {};
	//Vector2D(const Vector2D& v) : x_(v.x_), y_(v.y_) {}
	Vector2D(double x, double y) : x_(x), y_(y) {};
	virtual ~Vector2D() {}
#pragma region Getters
	inline Vector2D getVec() const { return { x_,y_ }; };
	inline double getX() const { return x_; };
	inline double getY() const { return y_; };
#pragma endregion

#pragma region Setters
	void setVec(Vector2D value) { x_ = value.getX(); y_ = value.getY(); };
	void setX(double x) { x_ = x; };
	void setY(double y) { y_ = y; };
#pragma endregion

#pragma region Operators																			 
	inline Vector2D operator+(const Vector2D& v) const { return Vector2D(x_ + v.x_, y_ + v.y_); } // Suma de vectores
	inline Vector2D operator-(const Vector2D& v) const { return Vector2D(x_ - v.x_, y_ - v.y_); } // Resta de vectores
	inline Vector2D operator*(double d) const { return Vector2D(x_ * d, y_ * d); }				  // Multiplicación vector * número
	inline double operator *(const Vector2D& d) const { return d.x_ * x_ + d.y_ * y_; }			  // Multiplicación vector * vector
	Vector2D operator/(double d) const { return Vector2D(x_ / d, y_ / d); }						  // División vector / número
	inline bool operator==(const Vector2D& v)const { return (x_ == v.x_ && y_ == v.y_); }		  // Comparación vector y vector
	inline bool operator!=(const Vector2D& v)const { return !(x_ == v.x_ && y_ == v.y_); }		  // Comparación vector y vector
#pragma endregion

#pragma region Operations
	void normalize();													// Normalización del vector
	double magnitude()const { return sqrt(pow(x_, 2) + pow(y_, 2)); }	// Módulo del vector
	inline double angle()const { return atan(y_ / x_); }				// Ángulo entre Vector2D y (0,0)
	double angle(const Vector2D& v) const;								// Ángulo entre dos vectores
	Vector2D rotate(double degrees) const;								// Rotación del vector x grados
#pragma endregion
};

typedef Vector2D Point2D;