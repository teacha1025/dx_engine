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
			/// <summary>
			/// ストップウォッチの作成
			/// </summary>
			stopwatch();
			/// <summary>
			/// 再スタート
			/// </summary>
			void restart();
			/// <summary>
			/// 再開
			/// </summary>
			void resume();
			/// <summary>
			/// 一時停止
			/// </summary>
			void suspention();
			/// <summary>
			/// ストップウォッチを止める
			/// </summary>
			void stop();

			/// <summary>
			/// 時間を取得
			/// </summary>
			/// <returns>経過時間(ミリ秒)</returns>
			long long get_msec() const;
			/// <summary>
			/// 時間を取得
			/// </summary>
			/// <returns>経過時間(秒)</returns>
			double get_sec() const;
		};
	}
}