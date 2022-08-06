#include "DxLib.h"
#include "../details/file.h"
#include "../details/texture.h"
#include "../details/step.h"
#include "../details/draw_param.h"

namespace dx_engine {
	extern detail::_file file;
	texture::texture() {
		*this = texture(point<int>(64, 64));
	}

	texture::texture(const point<int>& size, const point<int>& pos, const point<int>& center, dx_engine::blend blend, byte param, int handle, bool turn, bool flip, double angle, double rate, dx_engine::filter mode) {
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
		_filter = mode;
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
		auto image_str = file.get(path);
		int r = GetImageSize_Mem(image_str.data(), (int)image_str.size(), &x, &y);
		if (r < 0) {
			*this = texture();
			return;
		}
		_size = { SCAST(double, x), SCAST(double, y) };
		_center = _size / 2.0;
		_position = {};

		auto result = CreateGraphFromMem(image_str.data(), (int)image_str.size());
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
		auto image_str = file.get(path);
		int r = GetImageSize_Mem(image_str.data(), (int)image_str.size(), &x, &y);
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
		auto result = CreateDivGraphFromMem(image_str.data(), (int)image_str.size(), divnum.x * divnum.y, divnum.x, divnum.y, SCAST(int, _size.x), SCAST(int, _size.y), &_div_handle[0]);
		if (result < 0) {
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



	texture& texture::centered(const dx_engine::point<double>& center) {
		_center = center;
		return *this;
	}
	texture& texture::rotateed(double angle) {
		_angle = angle;
		return *this;
	}
	texture& texture::blend(dx_engine::blend mode, range<0, 255> param) {
		_blend = mode;
		_blendparam = param;
		return *this;
	}
	texture& texture::filter(dx_engine::filter mode) {
		_filter = mode;
		return *this;
	}
	texture& texture::at(const dx_engine::point<double>& position) {
		_position = position;
		return *this;
	}
	texture& texture::extended(double rate) {
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
	texture& texture::trans(bool flag) {
		_istrans = flag;
		return *this;
	}

	texture texture::operator [](const uint& i)const {
		if (!_isdiv) {
			return *this;
		}
		else if (0 <= i && i < _div_handle.size()) {
			return texture(_size, _position, _center, _blend, _blendparam, _div_handle.at(i), _isturn, _isflip, _angle, _rate, _filter);
		}
		else {
			int h = MakeGraph(SCAST(int, _size.x), SCAST(int, _size.y));
			FillGraph(h, 255, 255, 255);
			return texture(_size, _position, _center, _blend, _blendparam, h, _isturn, _isflip, _angle, _rate, _filter);
		}
	}

	point<double> texture::position() const {
		return _position;
	}

	void texture::draw() {
		if (_isdiv) {
			_handle = MakeGraph(SCAST(int, _size.x), SCAST(int, _size.y));
			FillGraph(_handle, 255, 255, 255);
		}
		SetDrawBlendMode(SCAST(int, _blend), _blendparam);
		SetDrawMode(SCAST(int, _filter));
		if (_center == _size / 2.0) {
			DrawRotaGraphF(SCAST(float, _position.x), SCAST(float, _position.y), _rate, _angle, _handle, _istrans, _isturn, _isflip);
		}
		else {
			DrawRotaGraph2F(SCAST(float, _position.x), SCAST(float, _position.y), SCAST(float, _center.x), SCAST(float, _center.y), _rate, _angle, _handle, _istrans, _isturn, _isflip);
		}
	}

	void texture::modofication_draw(const std::array<point<double>, 4>& position) {
		SetDrawBlendMode(SCAST(int, _blend), _blendparam);
		SetDrawMode(SCAST(int, _filter));
		DrawModiGraphF(SCAST(float, position.at(0).x), SCAST(float, position.at(0).y), SCAST(float, position.at(1).x), SCAST(float, position.at(1).y), SCAST(float, position.at(2).x), SCAST(float, position.at(2).y), SCAST(float, position.at(3).x), SCAST(float, position.at(3).y), _handle, _istrans);
	}
}