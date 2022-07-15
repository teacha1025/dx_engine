#pragma once
#include <algorithm>
#include "def.h"

namespace dx_engine {
	template<auto min, decltype(min) max>
	struct range {
	private:
		using type = decltype(min);
		type val;
	public:

		constexpr range() : val(min) {}
		constexpr range(type v) : val(std::clamp(v, min, max)) {}

		constexpr type get() const {
			return std::clamp(val, min, max);
		}

		range operator = (type v)&& {
			val = std::clamp(v, min, max);
			return std::move(*this);
		}

		range& operator = (type v)& {
			val = std::clamp(v, min, max);
			return *this;
		}

		operator type () const{
			return get();
		}
	};
}