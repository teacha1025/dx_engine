#define NOMINMAX
#include "../details/clock.h"
#include "../details/def.h"

namespace dx_engine {
	namespace clock {
		stopwatch::stopwatch() {
			is_active = true;
			is_sus = false;
			sum_time = 0;
			start_time = std::chrono::system_clock::now();
		}
		void stopwatch::restart() {
			is_sus = false;
			is_active = true;
			start_time = std::chrono::system_clock::now();
			sum_time = 0;
		}
		void stopwatch::resume() {
			if (!is_active) return;
			if (is_sus) {
				is_sus = false;
				start_time = std::chrono::system_clock::now();
			}
		}
		void stopwatch::suspention() {
			if (!is_active) return;
			sum_time = get_msec();
			is_sus = true;
		}
		void stopwatch::stop() {
			if (!is_active) return;
			sum_time = get_msec();
			is_sus = true;
		}

		long long stopwatch::get_msec() const {
			if (is_sus) {
				return sum_time;
			}
			else {
				auto now = std::chrono::system_clock::now();
				return std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count() + sum_time;
			}
		}
		double stopwatch::get_sec() const {
			return get_msec() / 1000.0;
		}
	}
}