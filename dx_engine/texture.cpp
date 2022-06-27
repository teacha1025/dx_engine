#include "DxLib.h"
#include "texture.h"
#include "step.h"

namespace dx_engine {
	texture::texture() {
		*this = texture(point<int>(64, 64));
	}

	texture::texture(const point<int>& size, const color& fill_color) {
		_handle = MakeGraph(size.x, size.y);
		_size = size;
		_center = size / 2.0;
		_position = {};
		FillGraph(_handle, fill_color.r, fill_color.g, fill_color.b);
	}

	texture::texture(const int& handle) {
		if (handle < 0) {
			*this = texture();
			return;
		}
		_handle = handle;
		float x, y;
		GetGraphSizeF(handle, &x, &y);
		_size = { SCAST(double, x), SCAST(double, y) };
		_center = _size / 2.0;
		_position = {};
	}

	texture::texture(const std::string& path) {
		int x, y;
		_isdiv = false;
		int r = GetImageSize_File(path.c_str(), &x, &y);
		if (r < 0) {
			*this = texture();
			return;
		}
		_size = { SCAST(double, x), SCAST(double, y) };
		_center = _size / 2.0;
		_position = {};

		auto result = LoadGraph(path.c_str());
		if (result < 0) {
			*this = texture(_size);
			return;
		}
		_handle = result;
	}


	texture::texture(const std::string& path, const point<int>& divnum) {
		int x, y;
		_isdiv = true;
		_div_num = divnum;
		int r = GetImageSize_File(path.c_str(), &x, &y);
		if (r < 0) {
			_size = { x,y };
			int handle = texture(point<int>(x, y))._handle;
			for (auto& h : step(divnum.x* divnum.y)) {
				_div_handle.push_back(handle);
			}
			return;
		}
		_size = { SCAST(double, x), SCAST(double, y) };
		_size /= divnum;
		_center = _size / 2.0;

		_div_handle.resize(SCAST(size_t, divnum.x * divnum.y));
		auto resutlt = LoadDivGraphF(path.c_str(), divnum.x * divnum.y, divnum.x, divnum.y, SCAST(float, _size.x), SCAST(float, _size.y), &_div_handle[0]);
		if (resutlt < 0) {
			int handle = texture(point<int>(x, y))._handle;
			_div_handle.clear();
			for (auto& h : step(divnum.x* divnum.y)) {
				_div_handle.at(h) = handle;
			}
			return;
		}
	}



	texture& texture::centered(const dx_engine::point<float>& center) {
		_center = center;
		return *this;
	}
	texture& texture::rotateed(float angle) {
		_angle = angle;
		return *this;
	}
	texture& texture::blend(dx_engine::blend mode, int param) {
		_blend = mode;
		_blendparam = param;
		return *this;
	}
	texture& texture::at(const dx_engine::point<float>& position) {
		_position = position;
		return *this;
	}
	texture& texture::extended(float rate) {
		_rate = rate;
		return *this;
	}
	texture& texture::turned(bool flag) {
		_isturn = flag;
		return *this;
	}
	texture& texture::fliped(bool flag) {
		_isflip = flag;
		return *this;
	}

	texture texture::operator [](const uint& i)const {
		if (!_isdiv) {
			return *this;
		}
		else if (0 <= i && i < _div_handle.size()) {
			return texture(_div_handle.at(i));
		}
		else {
			int h = MakeGraph(SCAST(int, _size.x), SCAST(int, _size.y));
			FillGraph(h, 255, 255, 255);
			return texture(h);
		}
	}

	point<float> texture::position() const {
		return _position;
	}

	void texture::draw() {
		if (_isdiv) {
			_handle = MakeGraph(SCAST(int, _size.x), SCAST(int, _size.y));
			FillGraph(_handle, 255, 255, 255);
		}
		SetDrawBlendMode(SCAST(int, _blend), _blendparam);
		SetDrawMode(SCAST(int, _draw_mode));
		if (_center == _size / 2.0) {
			DrawRotaGraphF(SCAST(float, _position.x), SCAST(float, _position.y), _rate, _angle, _handle, TRUE, _isturn, _isflip);
		}
		else {
			DrawRotaGraph2F(SCAST(float, _position.x), SCAST(float, _position.y), SCAST(float, _center.x), SCAST(float, _center.y), _rate, _angle, _handle, TRUE, _isturn, _isflip);
		}
	}
}