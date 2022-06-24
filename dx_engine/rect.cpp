#include "DxLib.h"
#include "dx_engine.h"

namespace dx_engine {
	rect::rect() {
		resize({ 64,64 });
		_center = { 32,32 };
	}

	rect::rect(const point<float> size) {
		resize(size);
		_center = size / 2.0f;
	}

	point<float> rect::size() const {
		return _size;
	}

	void rect::resize(const point<float>& size) {
		_size = size;
	}

	void rect::draw() {
		SetDrawBlendMode(static_cast<int>(_blend), _blendparam);
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
		DrawQuadrangleAA(static_cast<float>(p1.x), static_cast<float>(p1.y), static_cast<float>(p2.x), static_cast<float>(p2.y), static_cast<float>(p3.x), static_cast<float>(p3.y), static_cast<float>(p4.x), static_cast<float>(p4.y), _color.to_int(), true);
	}
}