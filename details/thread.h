#pragma once
#include <thread>
#include <future>
#include <vector>
#include <unordered_map>
#include "logger.h"
//http://aziogroup.blogspot.com/2016/05/stdasync.html
//https://stackoverflow.com/questions/9094422/how-to-check-if-a-stdthread-is-still-running

namespace dx_engine {
	extern logger log;
	namespace detail {
		class thread {
		private:
			using id = uint32_t;
			const bool finished = true;

			id _counter = 0u;
			std::unordered_map<id, bool> states;
			std::vector<std::pair<id, std::future<void>>> threads;
			void check(id _id) {
				if (states.at(_id) == finished) return;
				auto i = 0u;
				for (i = 0u; i < threads.size(); i++) {
					if (threads.at(i).first == _id) {
						goto check_begin;
					}
				}
				return;
				check_begin:
				auto s = threads.at(i).second.wait_for(std::chrono::milliseconds(0));
				if (s == std::future_status::ready) {
					threads.at(i).second.get();
					states.at(_id) = finished;
				}
			}
		public:
			/// <summary>
			/// �X���b�h�̏�Ԃ��擾
			/// </summary>
			/// <param name="_id">�X���b�hID</param>
			/// <returns>�X���b�h������������</returns>
			bool get(id _id) {
				check(_id);
				return states.at(_id);
			}

			/// <summary>
			/// �X���b�h�̒ǉ�
			/// </summary>
			/// <param name="function">�񓯊�����������֐�</param>
			/// <returns>�X���b�hID</returns>
			[[nodiscard]] id add(std::function<void()> function) {
				auto t = std::make_pair(++_counter, std::async(std::launch::async, function));
				threads.emplace_back(std::move(t));
				states.insert(std::make_pair(_counter, !finished));
				return _counter;
			}

			void update() {
				for (auto&& th : threads) {
					check(th.first);
				}
			}

			~thread() {
				/*for (auto&& th : threads) {
					if (states.at(th.first) != finished) {
						th.second.get();
					}
				}*/
				/*try {

				}
				catch (...) {
					log.exception("terminate");
				}*/
			}
		};
	}
	extern detail::thread thread_manager;
}