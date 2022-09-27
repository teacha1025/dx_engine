#pragma once
#include <thread>
#include <unordered_map>

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

			}
		};
	}
}