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
			/// �X�g�b�v�E�H�b�`�̍쐬
			/// </summary>
			stopwatch();
			/// <summary>
			/// �ăX�^�[�g
			/// </summary>
			void restart();
			/// <summary>
			/// �ĊJ
			/// </summary>
			void resume();
			/// <summary>
			/// �ꎞ��~
			/// </summary>
			void suspention();
			/// <summary>
			/// �X�g�b�v�E�H�b�`���~�߂�
			/// </summary>
			void stop();

			/// <summary>
			/// ���Ԃ��擾
			/// </summary>
			/// <returns>�o�ߎ���(�~���b)</returns>
			long long get_msec() const;
			/// <summary>
			/// ���Ԃ��擾
			/// </summary>
			/// <returns>�o�ߎ���(�b)</returns>
			double get_sec() const;
		};
	}
}