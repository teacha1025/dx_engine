#pragma once
#include <vector>
#include <array>
#include "def.h"
#include "color.h"
#include "pallet.h"
#include "draw_param.h"
#include "point.h"
#include "range.h"

namespace dx_engine {
	class texture {
	private:
		point<float> _size{}, _position{}, _center{};
		blend _blend = blend::alpha;
		byte _blendparam = 255;

		int _handle = 0;
		std::vector<int> _div_handle;
		bool _isdiv = false;
		bool _isturn = false;
		bool _isflip = false;
		double _angle = 0.0, _rate = 1.0;
		point<int> _div_num = { 1,1 };
		int _draw_mode = DX_DRAWMODE_NEAREST;

		bool _failer = false;
	public:
		texture();
		texture(const point<int>& size, const color& fill_color = pallet::white);
		texture(const int& handle);
		texture(const std::string& path);
		texture(const std::string& path, const point<int>& divnum);

		texture& centered(const dx_engine::point<float>& center);
		texture& rotateed(float angle);
		texture& blend(dx_engine::blend mode, range<0, 255> param);
		texture& at(const dx_engine::point<float>& position);
		texture& extended(float rate);
		texture& turned(bool flag);
		texture& fliped(bool flag);

		point<float> position() const;

		void draw();

		void modofication_draw(const std::array<point<float>, 4>& position);

		texture operator [](const uint& i)const;
	};
}