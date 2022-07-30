#pragma once
#include <vector>
#include <array>
#include "shape.h"
#include "def.h"
#include "color.h"
#include "pallet.h"
#include "draw_param.h"
#include "point.h"
#include "range.h"

namespace dx_engine {
	class texture : public detail::draw_object{
	private:
		point<float> _size{}, _position{}, _center{};

		int _handle = 0;
		std::vector<int> _div_handle;
		bool _isdiv = false;
		bool _isturn = false;
		bool _isflip = false;
		double _angle = 0.0, _rate = 1.0;
		point<int> _div_num = { 1,1 };

		bool _failer = false;
		texture(const point<int>& size, const point<int>& pos, const point<int>& center, blend blend, byte param, int handle, bool turn, bool flip, double angle, double rate, filter mode);
	public:
		texture();
		texture(const point<int>& size, const color& fill_color = pallet::white);
		texture(int handle);
		texture(const std::string& path);
		texture(const std::string& path, const point<int>& divnum);

		texture& centered(const dx_engine::point<float>& center);
		texture& rotateed(float angle);
		texture& blend(dx_engine::blend mode, range<0, 255> param);
		texture& filter(dx_engine::filter mode);
		texture& at(const dx_engine::point<float>& position);
		texture& extended(float rate);
		texture& turned(bool flag);
		texture& fliped(bool flag);

		point<float> position() const;

		virtual void draw() override;

		void modofication_draw(const std::array<point<float>, 4>& position);

		texture operator [](const uint& i)const;
	};
}