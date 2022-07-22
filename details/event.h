#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "def.h"
#include "range.h"


namespace dx_engine {
	class event {
	public:
		virtual bool update(uint count) = 0;
	};

	class event_manager {
	private:
		std::vector<std::tuple<std::function<bool(int)>, std::shared_ptr<event>, uint>> _event_list;

	public:
		template<class event_t, class... Args>
		void add(Args&&... args) {
			std::function<bool(int)> p = &event_t(args...)::update;
			_event_list.push_back(std::make_pair(p, 0));
			
		}

		void update();
	};
}