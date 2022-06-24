#include "device_base.h"
#include <DxLib.h>
namespace dx_engine {
	namespace detail {
		unsigned int _device_base::count() const {
			return _press_count;
		}

		bool _device_base::press() const {
			return _state == device_state::press || _state == device_state::down;
		}

		bool _device_base::release() const {
			return _state == device_state::release;
		}

		bool _device_base::up() const {
			return _state == device_state::up;
		}

		bool _device_base::down() const {
			return _state == device_state::down;
		}
	}
}