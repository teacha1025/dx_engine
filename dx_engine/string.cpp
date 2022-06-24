#include <string>
#include "DxLib.h"
#include "dx_engine.h"

namespace dx_engine {
	string& string::centered(const point<float>& center) {
		_center = center;
		return *this;
	}
	string& string::colored(const color& color) {
		_color = color;
		return *this;
	}
	string& string::blend(dx_engine::blend mode, int param) {
		_blend = mode;
		_blendparam = param;
		return *this;
	}
	string& string::at(const point<float>& position) {
		_position = position;
		return *this;
	}

	point<float> string::position() const {
		return _position;
	}
	point<float> string::size() const {

	}
	void string::draw() {

	}
}