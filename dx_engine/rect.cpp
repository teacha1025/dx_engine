#include "DxLib.h"
#include "../details/def.h"
#include "../details/shape.h"

namespace dx_engine {
	rect::rect() {
		_size = { 64, 64 };
		_center = { 32,32 };
	}

	rect::rect(const point<double> size) {
		_size = size;
		_center = size / 2.0f;
	}

	point<double> rect::size() const {
		return _size;
	}

	void rect::resize(const point<double>& size) {
		_size = size;
	}

	void rect::draw() {
		SetDrawBlendMode(SCAST(int, _blend), _blendparam);
		SetDrawMode(SCAST(int, _filter));
		auto [p1, p2, p3, p4] = verteces();
		DrawQuadrangleAA(SCAST(float, p1.x), SCAST(float, p1.y), SCAST(float, p2.x), SCAST(float, p2.y), SCAST(float, p3.x), SCAST(float, p3.y), SCAST(float, p4.x), SCAST(float, p4.y), _color.to_int(), _fill_flag, _thick);
	}

	std::tuple<point<double>, point<double>, point<double>, point<double>> rect::verteces() const {
		point <float> _A = { 0,0 };
		point <float> _B = { _size.x,0 };
		point <float> _C = { 0,_size.y };
		point <float> _D = _size;

		_A -= _center;
		_B -= _center;
		_C -= _center;
		_D -= _center;
		auto p1 = vector::rotate(_A, _angle) + _position;
		auto p2 = vector::rotate(_B, _angle) + _position;
		auto p3 = vector::rotate(_D, _angle) + _position;
		auto p4 = vector::rotate(_C, _angle) + _position;

		return { p1,p2,p3,p4 };
	}

	line rect::edge() const {
		auto [p1, p2, p3, p4] = verteces();

		return dx_engine::line().at({ p1,p2,p3,p4,p1 });
	}
}