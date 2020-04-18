#include "Vector2D.h"

#pragma region Operators
void Vector2D::normalize() {
	double mag = magnitude();
	if (mag > 0.0) {
		x_ = x_ / mag;
		y_ = y_ / mag;
	}
}

double Vector2D::angle(const Vector2D& v) const
{
	double a2 = atan2(v.getX(), v.getY());
	double a1 = atan2(x_, y_);
	double sign = a1 > a2 ? 1 : -1;
	double angle = a1 - a2;
	double K = -sign * M_PI * 2;
	angle = (abs(K + angle) < abs(angle)) ? K + angle : angle;
	return angle * 180. / M_PI;
}
Vector2D Vector2D::rotate(double degrees) const
{
	Vector2D r;

	degrees = fmod(degrees, 360.0);
	if (degrees > 180.0) {
		degrees = degrees - 360.0;
	}
	else if (degrees <= -180.0) {
		degrees = 360.0 + degrees;
	}

	SDL_assert(degrees >= -180.0 && degrees <= 180.0); //Comprobación assert para los errores.

	double angle = degrees * M_PI / 180.0;
	double sine = sin(angle);
	double cosine = cos(angle);

	//rotation matix
	double matrix[2][2] = { { cosine, -sine }, { sine, cosine } };

	double x = x_;
	double y = y_;

	r.x_ = matrix[0][0] * x + matrix[0][1] * y;
	r.y_ = matrix[1][0] * x + matrix[1][1] * y;

	return r;
}
Vector2D Vector2D::getClosest(Vector2D& a,Vector2D& b)
{
	if (a.x_ == -1 && a.y_ == -1)
		return b;
	else if (b.x_ == -1 && b.y_ == -1) return a;
	else
	{
		double aMagnitud = abs(Vector2D(x_ - a.x_, y_ - a.y_).magnitude());
		double bMagnitud = abs(Vector2D(x_ - b.x_, y_ - b.y_).magnitude());
		return aMagnitud <= bMagnitud ? a : b;
	}

}
#pragma endregion