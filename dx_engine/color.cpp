#include "DxLib.h"
#include "../details/def.h"
#include "../details/color.h"

namespace dx_engine {
	unsigned int color::to_int() const {
		return GetColor(SCAST(int, r), SCAST(int, g), SCAST(int, b));
	}

	color::operator hsv() const {
		hsv out;
		double min, max, _r = r / 255.0, _g = g / 255.0, _b = b / 255.0;

		out.a = a;

		min = _r < _g ? _r : _g;
		min = min < _b ? min : _b;

		max = _r > _g ? _r : _g;
		max = max > _b ? max : _b;
		out.v = max;

		auto d = max - min;
		if (d == 0 || max == 0) {
			return out;
		}
		
		out.s = d / max;
		double h = 0;
		if (max == _r) {
			h = (_g - _b) / d;
		}
		else if(max == _g) {
			h = 2.0 + (_b - _r) / d;
		}
		else {
			h = 4.0 + (_r - _g) / d;
		}
		h *= 60;

		if (h < 0.0) h += 360;
		if (h > 360.0) h -= 360;
		out.h = (int)h;

		return out;
	}

	unsigned int hsv::to_int() const {
		return ((color)*this).to_int();
	}

	hsv::operator color() const {
		double hh, ff;
		long i;
		byte p, q, t, _v;
		color out;

		out.a = a;

		_v = (byte)(v * 255);

		if (s <= 0.0) {	   // < is bogus, just shuts up warnings
			out.r = _v;
			out.g = _v;
			out.b = _v;
		}
		else {
			hh = h;
			if (hh >= 360.0) hh = 0.0;
			hh /= 60.0;
			i = (long)hh;
			ff = hh - i;
			p = (byte)(_v * (1.0 - s));
			q = (byte)(_v * (1.0 - (s * ff)));
			t = (byte)(_v * (1.0 - (s * (1.0 - ff))));

			switch (i) {
			case 0:
				out.r = _v;
				out.g = t;
				out.b = p;
				break;
			case 1:
				out.r = q;
				out.g = _v;
				out.b = p;
				break;
			case 2:
				out.r = p;
				out.g = _v;
				out.b = t;
				break;

			case 3:
				out.r = p;
				out.g = q;
				out.b = _v;
				break;
			case 4:
				out.r = t;
				out.g = p;
				out.b = _v;
				break;
			case 5:
			default:
				out.r = _v;
				out.g = p;
				out.b = q;
				break;
			}
		}
		return out;
	}
}