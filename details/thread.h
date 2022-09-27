#pragma once
#include <thread>
#include <future>
#include <unordered_map>
//http://aziogroup.blogspot.com/2016/05/stdasync.html
//https://stackoverflow.com/questions/9094422/how-to-check-if-a-stdthread-is-still-running

namespace dx_engine {
	namespace detail {
		class thread {
		private:
			using id = std::thread::id;

			std::unordered_map<id, bool> states;
		public:
			bool get(id _id) {
				return states.at(_id);
			}

			template<class T, class ...args>
			void add(T function, args... arg) {
				std::future<int> th;
				th.wait_for(0);
			}
		};
	}
}