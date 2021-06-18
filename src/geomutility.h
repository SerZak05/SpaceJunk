#pragma once

namespace Geom {
	const double possibleError = 1e-9;
	const double PI = 3.14159265358979323846264338327950288419716939937510;

	template <typename T> inline int sign(T val) {
		return (T(0) < val) - (val < T(0));
	}

	//Returns angle in [-PI; PI)
	inline double angleToNorm(double angle) {
		if (angle < -PI)
			angle += 2 * PI;
		else if (angle >= PI)
			angle -= 2 * PI;
		return angle;
	}
}