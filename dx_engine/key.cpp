#include<DxLib.h>
#include "key.h"
namespace dx_engine {
	namespace detail {
		_key::_key(const unsigned int code) {
			_state = device_state::release;
			_code = code;
			_press_count = 0;
		}

		void _key::update(const char key[]) {
			auto tmp = _press_count;

			if (key[_code] != 0) {
				_press_count++;
				_state = _press_count > 1 ? device_state::press : device_state::down;
			}
			else {
				if (tmp > 0) {
					_state = device_state::up;
				}
				else {
					_state = device_state::release;
				}
				_press_count = 0;
			}
		}
	}
}