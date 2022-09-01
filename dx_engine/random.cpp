#include "../details/random.h"

namespace dx_engine {
	namespace detail {
		random_core::random_core() {
			seed = (int)time(NULL);
			set_seed(seed);
		}
		void random_core::set_seed(int seed) {
			mt = std::mt19937(seed);
		}
		bool random_core::prob(double p) {
			std::bernoulli_distribution rnd(p);
			return rnd(mt);
		}

		random_core rnd_core;
	}

	namespace random {
		int seed() {
			return detail::rnd_core.seed;
		}

		bool probability(double p) {
			return detail::rnd_core.prob(p);
		}

		color colors(bool alpha) {
			byte a = alpha ? 255 : get <byte>(0, 255);
			return color{ get<byte>(0,255), get<byte>(0,255) ,get<byte>(0,255), a };
		}
	}
}