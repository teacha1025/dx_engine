#pragma once
#include "def.h"
#include "range.h"

namespace dx_engine {
	namespace ease {
		namespace in {
			double sine(const range<0.0, 1.0>& t);
			double quad(const range<0.0, 1.0>& t);
			double cubic(const range<0.0, 1.0>& t);
			double quart(const range<0.0, 1.0>& t);
			double quint(const range<0.0, 1.0>& t);
			double expo(const range<0.0, 1.0>& t);
			double circ(const range<0.0, 1.0>& t);
			double back(const range<0.0, 1.0>& t);
			double elastic(const range<0.0, 1.0>& t);
			double bounce(const range<0.0, 1.0>& t);
		}
		namespace out {
			double sine(const range<0.0, 1.0>& t);
			double quad(const range<0.0, 1.0>& t);
			double cubic(const range<0.0, 1.0>& t);
			double quart(const range<0.0, 1.0>& t);
			double quint(const range<0.0, 1.0>& t);
			double expo(const range<0.0, 1.0>& t);
			double circ(const range<0.0, 1.0>& t);
			double back(const range<0.0, 1.0>& t);
			double elastic(const range<0.0, 1.0>& t);
			double bounce(const range<0.0, 1.0>& t);
		}
		namespace inout {
			double sine(const range<0.0, 1.0>& t);
			double quad(const range<0.0, 1.0>& t);
			double cubic(const range<0.0, 1.0>& t);
			double quart(const range<0.0, 1.0>& t);
			double quint(const range<0.0, 1.0>& t);
			double expo(const range<0.0, 1.0>& t);
			double circ(const range<0.0, 1.0>& t);
			double back(const range<0.0, 1.0>& t);
			double elastic(const range<0.0, 1.0>& t);
			double bounce(const range<0.0, 1.0>& t);
		}
	}
}