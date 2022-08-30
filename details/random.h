#pragma once
#include <random>
#include "def.h"
#include "color.h"
#include "point.h"
#include "range.h"


namespace dx_engine {
	namespace detail {
		class random_core {
		private:
			std::mt19937 mt;
		public:
			int seed = -1;
			random_core();
			void set_seed(int seed);

			template<std::_Integer_like T>
			T get(T min, T max) {
				std::uniform_int_distribution<long long> rand((long long)min, (long long)max);
				return (T)rand(mt);
			}
			template<std::floating_point T>
			T get(T min, T max) {
				std::uniform_real_distribution<T> rand(min, max);
				return rand(mt);
			}

			bool prob(double p);
		};
		extern random_core rnd_core;
	}
	namespace random {
		int seed();

		template<std::integral T>
		T get(T min, T max) {
			return detail::rnd_core.get<T>(min, max);
		}

		template<std::floating_point T>
		T get(T min, T max) {
			return detail::rnd_core.get<T>(min, max);
		}

		template<std::integral T>
		T get(T max) {
			return detail::rnd_core.get<T>(0, max);
		}

		template<std::floating_point T>
		T get(T max) {
			return detail::rnd_core.get<T>(0, max);
		}

		bool probability(double p);

		color colors(bool alpha = false);

		template<Number T>
		point<T> points(const point<T>& min, const point<T>& max) {
			return point<T>{get<T>(min.x, max.x), get<T>(min.x, max.x)};
		}

		template<Number T>
		point<T> points(const point<T>& max) {
			return point<T>{get<T>(0, max.x), get<T>(0, max.x)};
		}

		template<auto minimum, decltype(minimum) maximum>
		decltype(minimum) get(range<minimum, maximum> v) {
			return get<decltype(minimum)>(minimum, maximum);
		}
	}
}