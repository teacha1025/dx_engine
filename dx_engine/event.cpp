#include "../details/def.h"
#include "../details/event.h"


namespace dx_engine {
	void event_manager::add(func_type func) {
		_event_list.push_back(std::make_pair(func, 0));
	}

	void event_manager::update() {
		std::erase_if(_event_list, [](list_type& e) { return !e.first(e.second++); });
	}
}