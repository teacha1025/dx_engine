#pragma once
# include <chrono>
# include <coroutine>
# include <deque>
# include <set>
# include <map>
# include <thread>
# include <utility>
# include <algorithm>
# include <cstdint>

namespace dx_engine {
	namespace coroutine {
		/// @brief タスクキュー関連
		namespace TaskQueue
		{
			/// @brief タスクの管理に使用されるクロック型
			using Clock = uint64_t;

			/// @brief タスクの管理に使用されるタイムポイント型
			using TimePoint = Clock;

			/// @brief タスクの管理に使用されるハンドル型
			using Handle = std::coroutine_handle<>;

			/// @brief タスクの管理に使用されるデュレーション型
			using Duration = Clock;

			/// @brief 相対時間で期限を指定して、タスクキューのタスクを実行します。
			/// @param relTime 相対時間の期限
			void RunFor(const Duration& relTime);

			/// @brief 絶対時間で期限を指定して、タスクキューのタスクを実行します。
			/// @param absTime 絶対時間の期限
			void RunUntil(const TimePoint& absTime);
		}
	}
}
# include "task_queue.ipp"