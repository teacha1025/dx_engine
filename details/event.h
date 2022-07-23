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
		using func_type = std::function<bool(uint)>;
		using list_type = std::pair<func_type, uint>;
		std::vector<list_type> _event_list;

	public:
		template<class event_t, class... Args>
		void add(Args&&... args) {
			_event_list.push_back(std::make_pair(std::bind(&event::update, std::make_shared<event_t>(args...), std::placeholders::_1), 0));
		}

		void add(func_type func);

		void update();
	};
}