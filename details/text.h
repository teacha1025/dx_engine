#pragma once
#include <string>
#include "point.h"
#include "color.h"
#include "pallet.h"
#include "draw_param.h"
#include "def.h"
#include "range.h"
#include "shape.h"

namespace dx_engine {
	
	class text : public dx_engine::detail::draw_object {
	private:
		std::string _str;
		point<float> _position = { 0,0 }, _center = { 0,0 }, _size = { 0,0 };
		color _color = pallet::black, _edgecolor = pallet::black;
		double _rate = 1.0, _scale = 0.2;
		bool _light_mode = false;

		int _fonthandle = 0;

		static int FONT_LOAD_SIZE;

		void setsize();
	public:
		text() {
			_filter = filter::bilinear;
		}
		text(const text&) = default;
		text(const std::string& str);
		text(const char* str);
		template<Number T>
		text(const point<T>& pos) {
			_str = pos.to_string();
			setsize();
		}
		template<Number T>
		text(T number) {
			_str = std::to_string(number);
			setsize();
		}
		text& centered(const dx_engine::point<float>& center);
		text& colored(const dx_engine::color& color, const dx_engine::color& edge = pallet::black);
		text& blend(dx_engine::blend mode, range<0, 255> param);
		text& filter(dx_engine::filter mode);
		text& extended(double rate);
		text& at(const dx_engine::point<float>& position);

		point<float> position() const;
		point<float> size() const;

		std::string& get();

		void set_font(const std::string& fontname = "", dx_engine::uint size = 16, dx_engine::uint thick = 1, dx_engine::font_type type = font_type::normal, uint edgesize = -1, bool italic = false, bool light_mode = false);
		void draw();

		text operator = (const std::string& str);
		text operator = (const char* str);

		template<Number T>
		text operator = (T number) {
			this->_str = std::to_string(number);
			return *this;
		}
		template<Number T>
		text operator = (const point<T>& pos) {
			this->_str = pos.to_string();
			return *this;
		}

		static void load_font_size(int size);
	};

	std::vector<std::string> split(const std::string& s, char split_char, bool is_contain_lastempty);
	std::string replace_string(std::string source, const std::string& old_val, const std::string& new_val);
	std::wstring to_wstring(const std::string& src);
}