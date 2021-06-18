#include "vector.h"
#include <cmath>
#include <assert.h>
#include "merrors.h"


using namespace Geom;

bool Vector::isNull() const {
	return Vector(0, 0, 0) == *this;
}

bool Vector::operator==(const Vector& v) const {
	return abs(x - v.x) < possibleError && abs(y - v.y) < possibleError && abs(z - v.z) < possibleError;
}

Vector& Vector::add(const Vector& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector& Vector::mult(double k) {
	x *= k;
	y *= k;
	z *= k;
	return *this;
}

Vector& Vector::div(double k) {
	assert(abs(k) > 1e-9);
	x /= k;
	y /= k;
	z /= k;
	return *this;
}

Vector& Vector::rotate(double a) {
	double newx = x * cos(a) - y * sin(a);
	double newy = x * sin(a) + y * cos(a);
	x = newx;
	y = newy;
	return *this;
}

double Vector::angleBetween(const Vector& v) const {
	if (isNull()) {
		throw NullVectorException(this);
	}
	if (v.isNull()) {
		throw NullVectorException(&v);
	}
	return acos((*this * v) / (mag() * v.mag())) * sign(crossmult(*this, v));
}

double Vector::azimut() const {
	return NORTH_VECTOR.angleBetween(*this);
}

Vector& Vector::norm() {
	if (isNull()) throw NullVectorException(this);
	mult(1 / mag());
	return *this;
}

double Vector::mag2() const {
	return x * x + y * y + z * z;
}

double Vector::mag() const {
	return sqrt(mag2());
}

Vector Vector::operator-() const {
	return Geom::Vector(-x, -y, -z);
}

Vector operator+(const Vector& a, const Vector& b) {
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

Vector& operator+=(Vector& a, const Vector& b) {
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return a;
}

Vector operator-(const Vector& a, const Vector& b) {
	return a + (-b);
}

Vector& operator-=(Vector& a, const Vector& b) {
	return a += (-b);
}

double operator*(const Vector& a, const Vector& b) {
	return a.x * b.x + a.y * b.y;
}

Vector operator*(const Vector& a, double k) {
	return { a.x * k, a.y * k, a.z * k };
}

Vector& operator*=(Vector& a, double k) {
	a.x *= k;
	a.y *= k;
	a.z *= k;
	return a;
}

Vector operator*(double k, const Vector& a) {
	return a * k;
}

Vector operator/(const Vector& a, double k) {
	assert(abs(k) > 1e-9);
	return { a.x / k, a.y / k, a.z / k };
}

Vector& operator/=(Vector& a, double k) {
	assert(abs(k) > 1e-9);
	a.x /= k;
	a.y /= k;
	a.z /= k;
	return a;
}

double crossmult(const Vector& v, const Vector& u) {
	return v.x * u.y + v.y * u.x;
}