#pragma once
#include "def.h"
#include <chrono>

namespace dx_engine {
	namespace clock {
		/*class timer {

		};*/

		class stopwatch {
			std::chrono::system_clock::time_point start_time;
			long long sum_time = 0;
			bool is_active, is_sus;
		public:
			stopwatch();
			void restart();
			void resume();
			void suspention();
			void stop();

			long long get_msec() const;
			double get_sec() const;
		};
	}
}