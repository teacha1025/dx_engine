#pragma once
#include <cmath>
#include "point.h"

namespace dx_engine {
	namespace vector {
		template<typename t>
		double size_square(const point<t>& p) {
			return p.x * p.x + p.y * p.y;
		}

		template<typename t>
		double size(const point<t>& p) {
			return std::sqrt(SizeSquare(p));
		}

		template<typename t>
		point<t> rotate(const point<t>& p, const double& angle) {
			t x, y;
			x = p.x * std::cos(angle) - p.y * std::sin(angle);
			y = p.x * std::sin(angle) + p.y * std::cos(angle);
			return { x,y };
		}

		template<typename t>
		point<t> rotate_at(const point<t>& p, const point<t>& c, const double& angle) {
			return rotate(p - c, angle) + c;
		}

		template<typename t>
		point<t> set_length(const point<t>& p, const double& length) {
			if (size(p) == 0) {
				return { 0,0 };
			}
			auto v = p / size(p);
			return v * length;
		}

		template<typename t>
		t cross(const point<t>& v1, const point<t>& v2) {
			return v1.x * v2.y - v1.y * v2.x;
		}
	}
}