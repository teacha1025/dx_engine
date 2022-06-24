#include <string>
#include "DxLib.h"
#include "dx_engine.h"

namespace dx_engine {
	string::string(const std::string& str) {
		_str = str;
	}

	string::string(const char* str) {
		_str = str;
	}

	void string::set_font(const std::string& fontname, dx_engine::uint size, dx_engine::uint thick, dx_engine::font_type type, uint edgesize, bool italic) {
		if (fontname == "") {
			_fonthandle = 0;
		}
		else {
			_fonthandle = CreateFontToHandle(fontname.c_str(), size, thick, static_cast<int>(type), -1, edgesize, static_cast<int>(italic));
		}
	}

	string& string::centered(const point<float>& center) {
		_center = center;
		return *this;
	}
	string& string::colored(const color& color, const dx_engine::color& edge) {
		_color = color;
		_edgecolor = edge;
		return *this;
	}
	string& string::blend(dx_engine::blend mode, int param) {
		_blend = mode;
		_blendparam = param;
		return *this;
	}
	string& string::at(const point<float>& position) {
		_position = position;
		return *this;
	}

	point<float> string::position() const {
		return _position;
	}
	point<float> string::size() const {
		int x = 0, y = 0;
		if (_fonthandle > 0) {
			GetDrawStringSizeToHandle(&x, &y, nullptr, _str.c_str(), (int)strlenDx(_str.c_str()), _fonthandle);
		}
		else {
			GetDrawStringSize(&x, &y, nullptr, _str.c_str(), (int)strlenDx(_str.c_str()));
		}
		return { x, y };
	}
	void string::draw() {
		auto p = _position - _center;
		if (_fonthandle > 0) {
			DrawStringFToHandle(p.x, p.y, _str.c_str(), _color.to_int(), _fonthandle, _edgecolor.to_int());
		}
		else {
			DrawStringF(p.x, p.y, _str.c_str(), _color.to_int(), _edgecolor.to_int());
		}
	}

	std::string& string::get() {
		return _str;
	}

}