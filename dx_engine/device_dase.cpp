#include "../details/device_base.h"
#include <DxLib.h>
#include "../details/exception.h"
#ifdef min
#undef min
#undef max
#endif
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

	unsigned int inputs::count() const {
		return true;
	}

	bool inputs::press() const {
		if (!_left && !_right) {
			if (!_dev) {
				throw EXCEPT("input\'s device is null.");
			}
			else {
				return _dev->press();
			}
		}
		else {
			if (!_left || !_right) {
				throw EXCEPT("inputs is null.");
			}
			if (_is_or) {
				return _left->press() || _right->press();
			}
			else {
				return _left->press() && _right->press();
			}
		}
	}

	bool inputs::release() const {
		if (!_left && !_right) {
			if (!_dev) {
				throw EXCEPT("input\'s device is null.");
			}
			else {
				return _dev->release();
			}
		}
		else {
			if (!_left || !_right) {
				throw EXCEPT("inputs is null.");
			}
			if (_is_or) {
				return _left->release() && _right->release();
			}
			else {
				return !press();
			}
		}
	}

	bool inputs::up() const {
		if (!_left && !_right) {
			if (!_dev) {
				throw EXCEPT("input\'s device is null.");
			}
			else {
				return _dev->up();
			}
		}
		else {
			if (!_left || !_right) {
				throw EXCEPT("inputs is null.");
			}
			if (_is_or) {
				return _left->up() || _right->up();
			}
			else {
				return _left->up() && _right->up();
			}
		}
	}

	bool inputs::down() const {
		if (!_left && !_right) {
			if (!_dev) {
				throw EXCEPT("input\'s device is null.");
			}
			else {
				return _dev->down();
			}
		}
		else {
			if (!_left || !_right) {
				throw EXCEPT("inputs is null.");
			}
			if (_is_or) {
				return _left->down() || _right->down();
			}
			else {
				return _left->down() && _right->down();
			}
		}
	}
	inputs inputs::operator | (detail::_key& r) const{
		inputs i, l = *this;
		i._left = std::make_shared<inputs>();
		i._left->_dev = l._dev;
		i._left->_left = l._left;
		i._left->_right = l._right;
		i._left->_is_or = l._is_or;
		i._right = std::make_shared<inputs>();
		i._right->_dev = reinterpret_cast<inputs::device*>(&r);
		i._is_or = true;
		return i;
	}
	inputs inputs::operator | (detail::_mouse& r) const {
		inputs i, l = *this;
		i._left = std::make_shared<inputs>();
		i._left->_dev = l._dev;
		i._left->_left = l._left;
		i._left->_right = l._right;
		i._left->_is_or = l._is_or;
		i._right = std::make_shared<inputs>();
		i._right->_dev = reinterpret_cast<inputs::device*>(&r);
		i._is_or = true;
		return i;
	}
	inputs inputs::operator | (inputs r) const{
		inputs i, l = *this;
		i._left = std::make_shared<inputs>();
		i._left->_dev = l._dev;
		i._left->_left = l._left;
		i._left->_right = l._right;
		i._left->_is_or = l._is_or;
		i._right = std::make_shared<inputs>();
		i._right->_dev = r._dev;
		i._right->_left = r._left;
		i._right->_right = r._right;
		i._right->_is_or = r._is_or;
		i._is_or = true;
		return i;
	}	

	inputs inputs::operator & (detail::_key& r) const {
		inputs i, l = *this;
		i._left = std::make_shared<inputs>();
		i._left->_dev = l._dev;
		i._left->_left = l._left;
		i._left->_right = l._right;
		i._left->_is_or = l._is_or;
		i._right = std::make_shared<inputs>();
		i._right->_dev = reinterpret_cast<inputs::device*>(&r);
		i._is_or = false;
		return i;
	}
	inputs inputs::operator & (detail::_mouse& r) const {
		inputs i, l = *this;
		i._left = std::make_shared<inputs>();
		i._left->_dev = l._dev;
		i._left->_left = l._left;
		i._left->_right = l._right;
		i._left->_is_or = l._is_or;
		i._right = std::make_shared<inputs>();
		i._right->_dev = reinterpret_cast<inputs::device*>(&r);
		i._is_or = false;
		return i;
	}
	inputs inputs::operator & (inputs r) const {
		inputs i, l = *this;
		i._left = std::make_shared<inputs>();
		i._left->_dev = l._dev;
		i._left->_left = l._left;
		i._left->_right = l._right;
		i._left->_is_or = l._is_or;
		i._right = std::make_shared<inputs>();
		i._right->_dev = r._dev;
		i._right->_left = r._left;
		i._right->_right = r._right;
		i._right->_is_or = r._is_or;
		i._is_or = false;
		return i;
	}

	inputs::inputs(detail::_key& key) {
		this->_dev = reinterpret_cast<device*>(&key);
	}
	inputs::inputs(detail::_mouse& mouse) {
		this->_dev = reinterpret_cast<device*>(&mouse);
	}
	inputs::inputs(const inputs& i) {
		this->_dev = i._dev;
		this->_left = i._left;
		this->_right = i._right;
		this->_is_or = i._is_or;
	}
}