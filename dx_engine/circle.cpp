#include "DxLib.h"
#include "../details/def.h"
#include "../details/shape.h"
#include "../details/draw_param.h"

namespace dx_engine {
	circle::circle() {
		_r = {};
		_center = { 0,0 };
	}

	circle::circle(double r) {
		resize(r);
		_center = { 0,0 };
	}

	double circle::size() const {
		return _r;
	}

	void circle::resize(double r) {
		_r = r;
	}

	void circle::draw() {
		SetDrawBlendMode(SCAST(int, _blend), _blendparam);
		SetDrawMode(SCAST(int, _filter));

		DrawCircleAA(SCAST(float, _position.x - _center.x), SCAST(float, _position.y - _center.y), SCAST(float, _r), (int)(_r * 3), _color.to_int(), _fill_flag, _thick);
	}
}