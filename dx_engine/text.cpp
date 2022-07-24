#include <string>
#include <sstream>
#include <vector>
#include "DxLib.h"
#include "../details/def.h"
#include "../details/text.h"

namespace dx_engine {
	text::text(const std::string& str) {
		_str = str;
		setsize();
	}

	text::text(const char* str) {
		_str = str;
		setsize();
	}

	void text::set_font(const std::string& fontname, dx_engine::uint size, dx_engine::uint thick, dx_engine::font_type type, uint edgesize, bool italic) {
		if (fontname == "") {
			_fonthandle = 0;
		}
		else {
			_fonthandle = CreateFontToHandle(fontname.c_str(), size, thick, SCAST(int, type), -1, edgesize, SCAST(int, italic));
		}
		setsize();
	}

	text& text::centered(const point<float>& center) {
		_center = center;
		return *this;
	}
	text& text::colored(const color& color, const dx_engine::color& edge) {
		_color = color;
		_edgecolor = edge;
		return *this;
	}
	text& text::blend(dx_engine::blend mode, range<0, 255> param) {
		_blend = mode;
		_blendparam = param.get();
		return *this;
	}
	text& text::filter(dx_engine::filter mode) {
		_filter = mode;
		return *this;
	}
	text& text::at(const point<float>& position) {
		_position = position;
		return *this;
	}

	point<float> text::position() const {
		return _position;
	}
	point<float> text::size() const {
		return _size;
	}
	void text::draw() {
		SetDrawBlendMode(SCAST(int, _blend), _blendparam);
		SetDrawMode(SCAST(int, _filter));
		auto p = _position - _center;
		if (_fonthandle > 0) {
			DrawStringFToHandle(p.x, p.y, _str.c_str(), _color.to_int(), _fonthandle, _edgecolor.to_int());
		}
		else {
			DrawStringF(p.x, p.y, _str.c_str(), _color.to_int(), _edgecolor.to_int());
		}
	}

	std::string& text::get() {
		return _str;
	}

	void text::setsize() {
		int x = 0, y = 0;
		if (_fonthandle > 0) {
			GetDrawStringSizeToHandle(&x, &y, nullptr, _str.c_str(), (int)strlenDx(_str.c_str()), _fonthandle);
		}
		else {
			GetDrawStringSize(&x, &y, nullptr, _str.c_str(), (int)strlenDx(_str.c_str()));
		}
		_size = { SCAST(float, x), SCAST(float, y) };
	}

	text text::operator = (const std::string& str) {
		this->_str = str;
		setsize();
		return *this;
	}
	text text::operator = (const char* str) {
		this->_str = str;
		setsize();
		return *this;
	}


	std::vector<std::string> split(const std::string& s, char split_char, bool is_contain_lastempty) {
		std::vector<std::string> v;
		std::stringstream ss(s);
		std::string buf;
		while (std::getline(ss, buf, split_char)) {
			v.emplace_back(buf);
		}
		if (!is_contain_lastempty && !s.empty() && s.back() == ',') {
			v.emplace_back();
		}

		return v;
	}

	std::string replace_string(std::string source, const std::string& old_val, const std::string& new_val) {
		std::string::size_type  Pos(source.find(old_val));

		while (Pos != std::string::npos)
		{
			source.replace(Pos, old_val.length(), new_val);
			Pos = source.find(old_val, Pos + new_val.length());
		}

		return source;
	}


	std::wstring to_wstring(const std::string& src) {
		int len = ::MultiByteToWideChar(CP_ACP, 0, src.c_str(), -1, nullptr, 0);
		wchar_t* wsbuf = (wchar_t*)new wchar_t[len];
		::MultiByteToWideChar(CP_ACP, 0, src.c_str(), -1, wsbuf, len);
		std::wstring ws(wsbuf, wsbuf + len - 1);
		delete[] wsbuf;
		return ws;
	}
}