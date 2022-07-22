#include "../details/def.h"
#include "../details/event.h"


namespace dx_engine {
	void event_manager::update() {
		std::erase_if(_event_list, [](std::pair<std::shared_ptr<std::function<bool(uint)>>, uint>& e) {return !e.first.get()->operator()(e.second++); });
	}
}