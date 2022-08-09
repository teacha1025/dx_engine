#pragma once
#include <vector>
#include <string>
#include "def.h"

namespace dx_engine {
	std::vector<std::string> split(const std::string& str, const std::string& splt);

	constexpr double degree(double radian) {
		return radian * 180.0 * std::numbers::inv_pi;
	}
	constexpr double radian(double degree) {
		return degree * std::numbers::pi / 180.0;
	}

	constexpr float degree_f(float radian) {
		return radian * 180.0f * std::numbers::inv_pi_v<float>;
	}
	constexpr float radian_f(float degree) {
		return degree * std::numbers::pi_v<float> / 180.0f;
	}

	constexpr uint factorial(uint n) {
		return n > 1u ? n * factorial(n - 1) : 1u;
	}
	constexpr uint binomial(uint n, uint k) {
		return factorial(n) / (factorial(k) * factorial(n - k));
	}
}