#include "DxLib.h"
#include "../details/texture.h"
#include "../details/step.h"
#include "../details/draw_param.h"

namespace dx_engine {
	texture::texture() {
		*this = texture(point<int>(64, 64));
	}

	texture::texture(const point<int>& size, const point<int>& pos, const point<int>& center, dx_engine::blend blend, byte param, int handle, bool turn, bool flip, double angle, double rate, int mode) {
		_size = size;
		_position = pos;
		_center = center;
		_blend = blend;
		_blendparam = param;
		_handle = handle;
		_isturn = turn;
		_isflip = flip;
		_angle = angle;
		_rate = rate;
		_draw_mode = mode;
	}

	texture::texture(const point<int>& size, const color& fill_color) {
		_handle = MakeGraph(size.x, size.y);
		_size = size;
		_center = size / 2.0;
		_position = {};
		FillGraph(_handle, fill_color.r, fill_color.g, fill_color.b);
	}

	texture::texture(int handle) {
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
			_failer = true;
			return;
		}
		_failer = false;
		_handle = result;
	}


	texture::texture(const std::string& path, const point<int>& divnum) {
		int x, y;
		_isdiv = true;
		_div_num = divnum;
		int r = GetImageSize_File(path.c_str(), &x, &y);
		if (r < 0) {
			_failer = true;
			_size = { 64,64 };
			int handle = texture(point<int>(64, 64))._handle;
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
			_failer = true;
			int handle = texture(point<int>(x, y))._handle;
			_div_handle.clear();
			for (auto& h : step(divnum.x* divnum.y)) {
				_div_handle.at(h) = handle;
			}
			return;
		}
		_failer = false;
	}



	texture& texture::centered(const dx_engine::point<float>& center) {
		_center = center;
		return *this;
	}
	texture& texture::rotateed(float angle) {
		_angle = angle;
		return *this;
	}
	texture& texture::blend(dx_engine::blend mode, range<0, 255> param) {
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
			return texture(_size, _position, _center, _blend, _blendparam, _div_handle.at(i), _isturn, _isflip, _angle, _rate, _draw_mode);
		}
		else {
			int h = MakeGraph(SCAST(int, _size.x), SCAST(int, _size.y));
			FillGraph(h, 255, 255, 255);
			return texture(_size, _position, _center, _blend, _blendparam, h, _isturn, _isflip, _angle, _rate, _draw_mode);
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

	void texture::modofication_draw(const std::array<point<float>, 4>& position) {
		SetDrawBlendMode(SCAST(int, _blend), _blendparam);
		SetDrawMode(SCAST(int, _draw_mode));
		DrawModiGraphF(position.at(0).x, position.at(0).y, position.at(1).x, position.at(1).y, position.at(2).x, position.at(2).y, position.at(3).x, position.at(3).y, _handle, TRUE);
	}
}