#pragma once
#include "shape.h"
#include "vector.h"

namespace dx_engine {
	template<Number t>
	bool collision(point<t> a, point<t> b) {
		return a == b;
	}

	template<Number t>
	bool collision(point<t> p, line l) {
		auto lp = l.position();
		if (lp.empty()) {
			return false;
		}
		if (lp.size() == 1u) {
			return p == lp.at(0);
		}
		for (size_t i = 0u; i < lp.size() - 1u; i++) {
			point<double> ab = lp.at(i + 1u) - lp.at(i), ap = p - lp.at(i);
			double s_ab = vector::size(ab), s_ap = vector::size(ap);
			if (vector::dot(ab, ap) == s_ab * s_ap) {
				if (s_ab >= s_ap) {
					return true;
				}
			}
		}

		return false;
	}

	template<Number t>
	bool collision(line l, point<t> p) {
		return collision(p, l);
	}

	template<Number t>
	bool collision(circle c, point<t> p) {
		return vector::size_square(c.position() - c.center() - p) < c.size() * c.size();
	}

	template<Number t>
	bool collision(point<t> p, circle c) {
		return collision(c, p);
	}

	bool collision(line l1, line l2);

	bool collision(circle c, line l);

	bool collision(line l, circle c);

	bool collision(circle c1, circle c2);

	template<Number t>
	bool collision(point<t> p, rect r) {
		auto [a, b, c, d] = r.verteces();

		if (
			vector::cross(b - a, p - a) > 0 &&
			vector::cross(c - b, p - b) > 0 &&
			vector::cross(d - c, p - c) > 0 &&
			vector::cross(a - d, p - d) > 0
			) {
			return true;
		}
		return false;
	}

	template<Number t>
	bool collision(rect r, point<t> p) {
		return collision(p, r);
	}

	bool collision(circle c, rect r);

	bool collision(rect r, circle c);

	bool collision(rect r, line l);

	bool collision(line l, rect r);

	bool collision(rect r1, rect r2);
}