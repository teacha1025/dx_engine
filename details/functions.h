#pragma once
#include <vector>
#include <string>
#include "def.h"

namespace dx_engine {
	std::vector<std::string> split(const std::string& str, const std::string& splt);

	constexpr double degree(double radian);
	constexpr double radian(double degree);

	constexpr float degree_f(float radian);
	constexpr float radian_f(float degree);

	constexpr uint factorial(uint n);
	constexpr uint binomial(uint n, uint k);
	constexpr double bernsterin(uint n, uint i, double t);
}