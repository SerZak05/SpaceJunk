#pragma once

namespace Geom {
	const double possibleError = 1e-9;

	template <typename T> int sign(T val) {
		return (T(0) < val) - (val < T(0));
	}
}