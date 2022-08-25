#include "../details/device_base.h"
#include <DxLib.h>
namespace dx_engine {
	namespace detail {
		unsigned int input_base::count() const {
			return _press_count;
		}

		bool input_base::press() const {
			return _state == device_state::press || _state == device_state::down;
		}

		bool input_base::release() const {
			return _state == device_state::release;
		}

		bool input_base::up() const {
			return _state == device_state::up;
		}

		bool input_base::down() const {
			return _state == device_state::down;
		}
	}
}