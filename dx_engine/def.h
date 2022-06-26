#pragma once
#include <numbers>

#ifndef SCAST
#define SCAST(t, v) static_cast<t>((v))
#endif

#ifndef define
#define define constexpr auto
#endif

namespace dx_engine {
	define PI = std::numbers::pi;
	define PI_F = std::numbers::pi_v<float>;
	define PI_2 = std::numbers::pi * 2.0;
	define PI_2F = std::numbers::pi_v<float> *2.0f;

	using uint = unsigned int;
}