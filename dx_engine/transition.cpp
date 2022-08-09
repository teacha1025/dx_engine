#include <cmath>
#include <vector>
#include "../details/def.h"
#include "../details/range.h"
#include "../details/point.h"
#include "../details/functions.h"
#include "../details/transition.h"

define pi = dx_engine::PI;
define dpi = pi * 2.0;
define hpi = pi / 2.0;
define c1 = 1.70158;
define c2 = c1 * 1.525;
define c3 = c1 + 1;
define c4 = dpi / 3.0;
define c5 = dpi / 4.5;
define n1 = 7.6525;
define d1 = 2.75;

#define t T.get()
#define it (1.0 - t)

namespace dx_engine {
	constexpr double cexp_pow(double p, uint n)
	{
		double s = 1.0;

		for (uint k = 0; k < n; k++)
		{
			s *= p;
		}
		return s;
	}
	constexpr double bernsterin(uint n, uint i, double _t) {
		return binomial(n, i) * cexp_pow(_t, i) * cexp_pow(1 - _t, n - i);
	}
	constexpr double B_base() {

	}
	namespace ease {
		namespace in {
			double sine(const range<0.0, 1.0>& T) {
				return 1.0 - cos(t * hpi);
			}
			double quad(const range<0.0, 1.0>& T) {
				return t * t;
			}
			double cubic(const range<0.0, 1.0>& T) {
				return t * t * t;
			}
			double quart(const range<0.0, 1.0>& T) {
				return t * t * t * t;
			}
			double quint(const range<0.0, 1.0>& T) {
				return t * t * t * t * t;
			}
			double expo(const range<0.0, 1.0>& T) {
				return t == 0 ? 0 : pow(2, 10 * t - 10);
			}
			double circ(const range<0.0, 1.0>& T) {
				return 1 - sqrt(1 - pow(t, 2));
			}
			double back(const range<0.0, 1.0>& T) {
				return c3 * t * t * t - c1 * t * t;
			}
			double elastic(const range<0.0, 1.0>& T) {
				return t == 0 ? 0 : t == 1 ? 1 : -pow(2, 10 * t - 10) * sin((t * 10 - 10.75) * c4);
			}
			double bounce(const range<0.0, 1.0>& T) {
				return 1 - out::bounce(1.0 - t);
			}
		}
		namespace out {
			double sine(const range<0.0, 1.0>& T) {
				return sin(t * hpi);
			}
			double quad(const range<0.0, 1.0>& T) {
				return 1 - it * it;
			}
			double cubic(const range<0.0, 1.0>& T) {
				return 1 - it * it * it;
			}
			double quart(const range<0.0, 1.0>& T) {
				return 1 - it * it * it;
			}
			double quint(const range<0.0, 1.0>& T) {
				return 1 - it * it * it * it;
			}
			double expo(const range<0.0, 1.0>& T) {
				return t == 1 ? 1 : 1 - pow(2, -10 * t);
			}
			double circ(const range<0.0, 1.0>& T) {
				return sqrt(1 - pow(-it, 2));
			}
			double back(const range<0.0, 1.0>& T) {
				return 1 + c3 * pow(-it, 3) + c1 * pow(-it, 2);
			}
			double elastic(const range<0.0, 1.0>& T) {
				return t == 0 ? 0 : t == 1 ? 1 : pow(2, -10 * t) * sin((t * 10 - 0.75) * c4) + 1;
			}
			double bounce(const range<0.0, 1.0>& T) {
				if (t < 1 / d1) {
					return n1 * t * t;
				}
				else if (t < 2 / d1) {
					return n1 * pow(t - 1.5 / d1, 2) + 0.75;
				}
				else if (t < 2.5 / d1) {
					return n1 * pow(t - 2.25 / d1, 2) + 0.9375;
				}
				else {
					return n1 * pow(t - 2.625 / d1, 2) + 0.984375;
				}
			}
		}
		namespace inout {
			double sine(const range<0.0, 1.0>& T) {
				return -(cos(pi * t) - 1) / 2.0;
			}
			double quad(const range<0.0, 1.0>& T) {
				return t < 0.5 ? 2 * t * t : 1 - pow(-2 * t + 2, 2) / 2.0;
			}
			double cubic(const range<0.0, 1.0>& T) {
				return t < 0.5 ? 4 * t * t * t : 1 - pow(-2 * t + 2, 3) / 2.0;
			}
			double quart(const range<0.0, 1.0>& T) {
				return t < 0.5 ? 8 * t * t * t * t : 1 - pow(-2 * t + 2, 4) / 2.0;
			}
			double quint(const range<0.0, 1.0>& T) {
				return t < 0.5 ? 16 * t * t * t * t * t : 1 - pow(-2 * t + 2, 5) / 2.0;
			}
			double expo(const range<0.0, 1.0>& T) {
				return t == 0 ? 0 : t == 1 ? 1 : t < 0.5 ? pow(2, 20 * t - 10) / 2.0 : (2 - pow(2, -20 * t + 10)) / 2.0;
			}
			double circ(const range<0.0, 1.0>& T) {
				return t < 0.5 ? (1 - sqrt(1 - pow(2 * t, 2))) / 2.0 : (sqrt(1 - pow(-2 * t + 2, 2)) + 1) / 2.0;
			}
			double back(const range<0.0, 1.0>& T) {
				return t < 0.5 ? (pow(2 * t, 2) * ((c2 + 1) * 2 * t - c2)) / 2.0 : (pow(2 * t - 2, 2) * ((c2 + 1) * (t * 2 - 2) + c2) + 2) / 2.0;
			}
			double elastic(const range<0.0, 1.0>& T) {
				return t == 0 ? 0 : t == 1 ? 1 : t < 0.5 ? -(pow(2, 20 * t - 10) * sin((20 * t - 11.125) * c5)) / 2.0 : (pow(2, -20 * t + 10) * sin((20 * t - 11.125) * c5)) / 2.0 + 1;
			}
			double bounce(const range<0.0, 1.0>& T) {
				return t < 0.5 ? (1 - out::bounce(1 - 2 * t)) / 2.0 : (1 + out::bounce(2 * t - 1)) / 2.0;
			}
		}
		namespace lerp {
			point<double> bezier(std::vector<point<double>> cp, const range<0.0, 1.0>& T) {
				point<double> p{ 0,0 };
				for (uint i = 0; i < cp.size(); i++) {
					p += cp.at(i) * bernsterin(cp.size(), i, t);
				}
				return p;
			}
		}
	}
}