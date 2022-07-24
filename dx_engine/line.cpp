#include "DxLib.h"
#include "../details/def.h"
#include "../details/shape.h"

namespace dx_engine {
	line& line::at(const std::vector<point<float>>& point) {
		_position = point;
		return *this;
	}

	line& line::blend(dx_engine::blend mode, range<0, 255> param) {
		_blend = mode;
		_blendparam = param;
		return *this;
	}
	line& line::filter(dx_engine::filter mode) {
		_filter = mode;
		return *this;
	}
	line& line::colored(const color& color) {
		_color = color;
		return *this;
	}
	line& line::thick(float thick) {
		_thick = thick;
		return *this;
	}

	std::vector<point<float>> line::position() const {
		return _position;
	}

	void line::draw() {
		if (_position.empty()) {
			return;
		}
		if (_position.size() == 1ULL) {
			DrawCircleAA(_position.at(0).x, _position.at(0).y, _thick / 2, (int)(_thick * 3), _color.to_int(), TRUE);
			return;
		}
		for (int i = 0; i < _position.size() - 1; i++) {
			if (i != 0 && _thick > 1) {
				DrawCircleAA(_position.at(i).x, _position.at(i).y, _thick / 2 - 1, 16, _color.to_int(), TRUE);
			}
			DrawLineAA(_position.at(i).x, _position.at(i).y, _position.at(i + 1).x, _position.at(i + 1).y, _color.to_int(), _thick);
		}
	}

}