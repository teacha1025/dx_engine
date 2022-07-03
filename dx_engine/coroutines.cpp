#include "def.h"
#include "coroutines.h"

namespace dx_engine {
	namespace coroutines {
		[[nodiscard]] task wait(uint frame) {
			for (uint i = 0; i < frame; i++) {
				co_yield{};
			}
		}
	}
}