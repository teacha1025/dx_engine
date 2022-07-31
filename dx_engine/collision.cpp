#include "DxLib.h"
#include "../details/collision.h"
using namespace dx_engine::vector;

void nearest( dx_engine::point<double> A,  dx_engine::point<double> B,  dx_engine::point<double> p, dx_engine::point<double>* x) {
	auto v = B - A, ap = p - A, bp = p - B;
	if (dot(v, ap) <= 0) {
		*x = A;
	}
	else if (dot(v, bp) >= 0) {
		*x = B;
	}
	else {
		auto n = set_length(v, 1.0);
		*x = A + n * dot(n, ap);
	}
}

namespace dx_engine {

	bool collision(line l1, line l2) {
		auto l1p = l1.position(), l2p = l2.position();
		if (l1p.empty() || l2p.empty()) {
			return false;
		}
		if (l1p.size() == 1u) {
			return collision(l1p.at(0), l2);
		}
		if (l2p.size() == 1u) {
			return collision(l2p.at(0), l1);
		}
		for (size_t i = 0; i < l1p.size() - 1; i++) {
			for (size_t j = 0; j < l2p.size() - 1; j++) {
				point<double> ab = l1p.at(i + 1) - l1p.at(i), ac = l2p.at(j) - l1p.at(i), ad = l2p.at(j + 1) - l1p.at(i), ca = -ac, cb = l1p.at(i + 1) - l2p.at(j), cd = l2p.at(j + 1) - l2p.at(j);

				if (cross(ab, ac) * cross(ab, ad) <= 0 && cross(cd, ca) * cross(cd, cb) <= 0) {
					return true;
				}
			}
		}
		return false;
	}

	bool collision(circle c, line l) {
		auto lp = l.position();
		auto p = c.position() - c.center();
		if (lp.empty()) {
			return false;
		}
		if (lp.size() == 1u) {
			return collision(c, lp.at(0));
		}
		for (size_t i = 0; i < lp.size() - 1; i++) {
			auto x = p;
			nearest(lp.at(i), lp.at(i + 1), p, &x);
			if (collision(x, c)) {
				return true;
			}
		}

		return false;
	}

	bool collision(line l, circle c) {
		return collision(c, l);
	}

	bool collision(circle c1, circle c2) {
		return size_square((c1.position() - c1.center()) - (c2.position() - c2.center())) <= pow(c1.size() + c2.size(), 2);
	}

	bool collision(circle c, rect r) {
		return collision(r, c.position() - c.center()) || collision(r.edge(), c);
	}

	bool collision(rect r, circle c) {
		return collision(c, r);
	}

	bool collision(rect r, line l) {
		for (auto&& p : l.position()) {
			if (collision(r, p)) {
				return true;
			}
		}
		return collision(r.edge(), l);
	}

	bool collision(line l, rect r) {
		return collision(r, l);
	}

	bool collision(rect r1, rect r2) {
		return collision(r1, r2.edge()) || collision(r2, r1.edge());
	}
}