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
		/// @brief �^�X�N�L���[�֘A
		namespace TaskQueue
		{
			/// @brief �^�X�N�̊Ǘ��Ɏg�p�����N���b�N�^
			using Clock = uint64_t;

			/// @brief �^�X�N�̊Ǘ��Ɏg�p�����^�C���|�C���g�^
			using TimePoint = Clock;

			/// @brief �^�X�N�̊Ǘ��Ɏg�p�����n���h���^
			using Handle = std::coroutine_handle<>;

			/// @brief �^�X�N�̊Ǘ��Ɏg�p�����f�����[�V�����^
			using Duration = Clock;

			/// @brief ���Ύ��ԂŊ������w�肵�āA�^�X�N�L���[�̃^�X�N�����s���܂��B
			/// @param relTime ���Ύ��Ԃ̊���
			void RunFor(const Duration& relTime);

			/// @brief ��Ύ��ԂŊ������w�肵�āA�^�X�N�L���[�̃^�X�N�����s���܂��B
			/// @param absTime ��Ύ��Ԃ̊���
			void RunUntil(const TimePoint& absTime);
		}
	}
}
# include "task_queue.ipp"