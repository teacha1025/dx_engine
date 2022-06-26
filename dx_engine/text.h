#pragma once
#include <string>

#include "point.h"
#include "color.h"
#include "pallet.h"
#include "draw_param.h"
#include "def.h"
namespace dx_engine {
	class text {
	private:
		std::string _str;
		point<float> _position = { 0,0 }, _center = { 0,0 };
		color _color = pallet::black, _edgecolor = pallet::black;
		blend _blend = blend::alpha;
		byte _blendparam = 255;

		int _fonthandle = 0;
	public:
		text() = default;
		text(const text&) = default;
		text(const std::string& str);
		text(const char* str);
		text& centered(const dx_engine::point<float>& center);
		text& colored(const dx_engine::color& color, const dx_engine::color& edge = pallet::black);
		text& blend(dx_engine::blend mode, int param);
		text& at(const dx_engine::point<float>& position);

		point<float> position() const;
		point<float> size() const;

		std::string& get();

		void set_font(const std::string& fontname = "", dx_engine::uint size = 16, dx_engine::uint thick = 1, dx_engine::font_type type = font_type::normal, uint edgesize = -1, bool italic = false);
		void draw();

		text operator = (const std::string& str);
		text operator = (const char* str);
	};

}