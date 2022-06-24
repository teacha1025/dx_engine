#include "DxLib.h"
#include "dx_engine.h"

namespace dx_engine {
	circle::circle() {
		_center = { 0,0 };
	}

	circle::circle(float r) {
		resize(r);
		_center = { 0,0 };
	}

	float circle::size() const {
		return _r;
	}

	void circle::resize(float r) {
		_r = r;
	}

	void circle::draw() {
		SetDrawBlendMode(static_cast<int>(_blend), _blendparam);

		DrawCircleAA(_position.x - _center.x, _position.y - _center.y, _r, (int)(_r * 3), _color.to_int(), _fill_flag, _thick);
	}
}