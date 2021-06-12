#pragma once
#include "geomutility.h"
#include <ostream>
#include <fstream>


namespace Geom {
	const double PI = 3.14159265358979323846264338327950288419716939937510;
	class Vector {
	public:
		double x, y, z;
		Vector(double x, double y, double z = 0) : x(x), y(y), z(z) {}
		Vector() : x(0), y(0), z(0) {}
		Vector(const Vector& v) : x(v.x), y(v.y), z(v.z) {}

		bool isNull() const;
		bool operator==(const Vector& v) const;

		Vector& add(const Vector& v); // adds to this vector another vector, returns this
		Vector& mult(double k); // multiplies this vector by a number, returns this
		Vector& div(double k); // multiplies this vector by 1 over a number, returns this

		Vector& rotate(double a); // rotates this vector, returns this (only works in 2D)
		double angleBetween(const Vector&) const; // returns oriented angle between this and other vector
		double azimut() const; // returns angle (in rad) between y axis and the vector

		Vector& norm(); // normilizes this vector, returns this
		double mag2() const; // returns squared length of the vector
		double mag() const; // returns the length of the vector

		Vector operator-() const; // returns opposite vector
	};

	class NullVectorException {
	public:
		const Vector* errorVector;
		NullVectorException(const Vector* v) : errorVector(v) {}
	};

	const Geom::Vector NULL_VECTOR(0, 0, 0);
};


Geom::Vector operator+(const Geom::Vector&, const Geom::Vector&);
Geom::Vector& operator+=(Geom::Vector&, const Geom::Vector&);

Geom::Vector operator-(const Geom::Vector&, const Geom::Vector&);
Geom::Vector& operator-=(Geom::Vector&, const Geom::Vector&);

double operator*(const Geom::Vector&, const Geom::Vector&);

Geom::Vector operator*(const Geom::Vector&, double);
Geom::Vector operator*(double, const Geom::Vector&);
Geom::Vector& operator*=(Geom::Vector&, double);
Geom::Vector operator/(const Geom::Vector&, double);
Geom::Vector& operator/=(Geom::Vector&, double);
double crossmult(const Geom::Vector&, const Geom::Vector&);

template<class T>
T& operator<<(T& out, const Geom::Vector& v) {
	out << v.x << ' ' << v.y << ' ' << v.z;
	return out;
}
