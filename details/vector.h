#pragma once
#include <cmath>
#include "def.h"
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
			x = (t)(p.x * std::cos(angle) - p.y * std::sin(angle));
			y = (t)(p.x * std::sin(angle) + p.y * std::cos(angle));
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

		template<typename t>
		t dot(const point<t>& v1, const point<t>& v2) {
			return v1.x * v2.x + v1.y * v2.y;
		}

		template<typename t>
		double angle(const point<t>& v) {
			if (v.x == 0) {
				return v.y >= 0 ? PI_HALF : -PI_HALF;
			}
			if (v.y == 0) {
				return v.x >= 0 ? 0 : PI;
			}
			return atan(v.y / v.x);
		}

		template<typename t>
		double angle(const point<t>& v1, const point<t>& v2) {
			return angle(v2 - v1);
		}
	}
}