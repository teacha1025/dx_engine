#include "DxLib.h"
#include "../details/def.h"
#include "../details/shape.h"

namespace dx_engine {
	line& line::at(const std::vector<point<double>>& point) {
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

	line& line::round(bool flag) {
		_round_edge = flag;
		return *this;
	}

	std::vector<point<double>> line::position() const {
		return _position;
	}



	void line::draw() {
		if (_position.empty()) {
			return;
		}
		if (_position.size() == 1ULL) {
			DrawCircleAA(SCAST(float, _position.at(0).x), SCAST(float, _position.at(0).y), _thick / 2, (int)(_thick * 3), _color.to_int(), TRUE);
			return;
		}
		for (size_t i = 0; i < _position.size() - 1; i++) {
			DrawLineAA(SCAST(float, _position.at(i).x), SCAST(float, _position.at(i).y), SCAST(float, _position.at(i + 1).x), SCAST(float, _position.at(i + 1).y), _color.to_int(), _thick);
			if (i != 0 && _thick > 1) {
				if (_round_edge) {
					DrawCircleAA(SCAST(float, _position.at(i).x), SCAST(float, _position.at(i).y), _thick / 2 - 1, 16, _color.to_int(), TRUE);
				}
				else {
					auto& a = _position.at(i - 1), & b = _position.at(i), & c = _position.at(i + 1);
					auto ab = vector::angle(a, b), bc = vector::angle(b, c);
					point<double> A = { b.x - _thick / 2.0, b.y }, B = { b.x + _thick / 2.0, b.y };
					auto p1 = vector::rotate_at(A, b, ab + PI_HALF), p2 = vector::rotate_at(A, b, bc + PI_HALF), p3 = vector::rotate_at(A, b, ab - PI_HALF), p4 = vector::rotate_at(A, b, bc - PI_HALF);
					DrawQuadrangleAA(SCAST(float, p1.x), SCAST(float, p1.y), SCAST(float, p2.x), SCAST(float, p2.y), SCAST(float, p3.x), SCAST(float, p3.y), SCAST(float, p4.x), SCAST(float, p4.y), pallet::red.to_int(),TRUE);
				}
			}
			
		}
	}
}