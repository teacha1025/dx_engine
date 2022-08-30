#pragma once
#include <algorithm>
#include "def.h"

#undef min
#undef max
namespace dx_engine {
	template<auto minimum, decltype(minimum) maximum>
	struct range {
	private:
		using type = decltype(minimum);
		type val;
	public:

		constexpr range() : val(minimum) {}
		constexpr range(type v) : val(std::clamp(v, minimum, maximum)) {}

		constexpr type get() const {
			return std::clamp(val, minimum, maximum);
		}

		range operator = (type v)&& {
			val = std::clamp(v, minimum, maximum);
			return std::move(*this);
		}

		range& operator = (type v)& {
			val = std::clamp(v, minimum, maximum);
			return *this;
		}

		operator type () const{
			return get();
		}

		constexpr type max() const {
			return maximum;
		}

		constexpr type min() const {
			return minimum;
		}
	};
}