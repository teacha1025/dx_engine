#pragma once
#include "range.h"
#include <DxLib.h>

namespace dx_engine {
	struct hsv;
	struct color {
		byte r, g, b, a;
		constexpr color() :r(0), g(0), b(0), a(255) {}

		constexpr color(byte _r, byte _g, byte _b, byte _a = 255) : r(_r), g(_g), b(_b), a(_a) {}

		constexpr color(const color& color, byte _a) : r(color.r), g(color.g), b(color.b), a(_a) {}

		operator hsv() const;

		unsigned int to_int() const;
	};

	struct hsv {
		int h;
		double s, v;
		byte a;

		constexpr hsv() :h(0), s(0), v(0), a(255) {};
		constexpr hsv(range<0, 360> h, range<0.0, 1.0> s, range<0.0, 1.0> v, byte a = 255) :h(h.get()), s(s.get()), v(v.get()), a(a) {}
		constexpr hsv(const hsv& color, byte a) : h(color.h), s(color.s), v(color.v), a(a) {}

		operator color() const;

		unsigned int to_int() const;
	};
}