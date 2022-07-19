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
			T first_;
			T last_;
			T step_;
		public:
			//static_assert(std::is_integral<T>::value, "T must be a integer type");

			step(const T& First, const T& Last) : first_(First), last_(Last), step_(1) {
				assert(First <= Last);
			}

			class Iterator {
			private:
				T position_;
				T step_;
			public:
				Iterator(T Position, T Step) : position_(Position), step_(Step) {}

				bool operator!=(const Iterator& Rhs) {
					return position_ <= Rhs.position_;
				}

				Iterator& operator++() {
					position_ += step_;
					return *this;
				}

				T& operator*() {
					return position_;
				}
			};

			Iterator begin() {
				return Iterator(first_, step_);
			}

			Iterator end() {
				return Iterator(last_, step_);
			}

			step& steps(const T& Step) {
				assert(0 <= Step);
				step_ = Step;
				return *this;
			}
		};
	}

	template <detail::Integer T>
	detail::step<T> step(T first, T last) {
		return detail::step<T>(first, last);
	}

	template <detail::Integer T>
	detail::step<T> step(T number) {
		return detail::step<T>(0, number - 1);
	}
}