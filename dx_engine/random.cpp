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

		random_core rnd_core;
	}
}