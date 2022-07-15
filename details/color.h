#pragma once
#include <DxLib.h>

namespace dx_engine {
	struct color {
		byte r, g, b, a;
		constexpr color() :r(0), g(0), b(0), a(255) {}

		constexpr color(byte _r, byte _g, byte _b, byte _a = 255) : r(_r), g(_g), b(_b), a(_a) {}

		constexpr color(const color& color, byte _a) : r(color.r), g(color.g), b(color.b), a(_a) {}

		unsigned int to_int() const;
	};
}