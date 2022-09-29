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
		auto r = _r * _rate;
		auto c = _center * _rate;

		auto p = vector::rotate_at(_position, c, _angle);

		DrawCircleAA(SCAST(float, p.x - c.x), SCAST(float, p.y - c.y), SCAST(float, r), (int)(r * 3), _color.to_int(), _fill_flag, _thick);
	}
}