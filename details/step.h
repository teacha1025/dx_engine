#pragma once
#include <concepts>
#include <type_traits>
#include <cassert>
#include <ranges>

namespace dx_engine {
	namespace detail {
		template<typename T>
		concept Integer = std::integral<T>;

		template <Integer T>
		class step {
		private:
			T _max, count, interval;
		public:
			//static_assert(std::is_integral<T>::value, "T must be a integer type");

			step(const T& First, const T& Last, const T& Interval) : _max(Last + 1), interval(Interval), count(First) {
				//assert(First <= Last);
			}
			step(const T& Num, const T& Interval) : _max(Num), interval(Interval), count(0) {
				//assert(First <= Last);
			}

			step& begin() {
				return *this;
			}

			step& end() {
				return *this;
			}

			step& operator++() {
				count += interval;
				return *this;
			}
			bool operator !=(step&) {
				return count < _max;
			}
			T& operator* () {
				return count;
			}
		};
	}

	template <detail::Integer T>
	detail::step<T> step(T first, T last, T interval = 1) {
		return detail::step<T>(first, last, interval);
	}

	template <detail::Integer T>
	detail::step<T> step(T number) {
		return detail::step<T>(number, 1);
	}
}