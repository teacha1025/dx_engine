#pragma once
#include <string>
#include <format>
#include <vector>
#include <numbers>
#include <memory>
#include <map>
#include <functional>
#include <cassert>
#include <DxLib.h>

#include "def.h"
#include "details.h"
#include "draw_param.h"
#include "point.h"
#include "vector.h"
#include "color.h"
#include "pallet.h"
#include "text.h"
#include "scene.h"
#include "device.h"



namespace dx_engine {
	

	class rect : public detail::shape {
	private:
		point<float> _size;
	public:
		rect();
		rect(const dx_engine::point<float> size);

		point<float> size() const;
		void resize(const dx_engine::point<float>& size);

		void draw() override;
	};

	class circle : public detail::shape {
	private:
		float _r;
	public:
		circle();
		circle(float r);

		float size() const;
		void resize(float r);

		void draw() override;
	};

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
	public:
		texture();
		texture(const point<int>& size, const color& fill_color = pallet::white);
		texture(const int& handle);
		texture(const std::string& path);
		texture(const std::string& path, const point<int>& divnum);

		texture& centered(const dx_engine::point<float>& center);
		texture& rotateed(float angle);
		texture& blend(dx_engine::blend mode, int param);
		texture& at(const dx_engine::point<float>& position);
		texture& extended(float rate);
		texture& turned(bool flag);
		texture& fliped(bool flag);

		point<float> position() const;

		void draw();

		texture operator [](const uint& i)const;
	};

	class file final{

	};

	std::vector<std::string> split(const std::string& str, const std::string& splt);

	constexpr double degree(double radian);
	constexpr double radian(double degree);

	constexpr float degree_f(float radian);
	constexpr float radian_f(float degree);

	extern detail::_system system;
	extern detail::_window window;

}
