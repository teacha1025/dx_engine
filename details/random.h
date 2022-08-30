#pragma once
#include <random>
#include "def.h"


namespace dx_engine {
	namespace detail {
		class random_core {
		private:
			std::mt19937 mt;
		public:
			int seed = -1;
			random_core();
			void set_seed(int seed);

			template<std::integral T>
			T get(T min, T max) {
				std::uniform_int_distribution<T> rand(min, max);
				return rand(mt);
			}
			template<std::floating_point T>
			T get(T min, T max) {
				std::uniform_real_distribution<T> rand(min, max);
				return rand(mt);
			}
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

		template<>
		bool get<bool>(double p) {
			double v = get<T>(0.0, 1.0);
			return v <= p ? true : false;
		}
	}
}