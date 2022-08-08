#pragma once
#include <vector>
#include <string>

namespace dx_engine {
	std::vector<std::string> split(const std::string& str, const std::string& splt);

	constexpr double degree(double radian);
	constexpr double radian(double degree);

	constexpr float degree_f(float radian);
	constexpr float radian_f(float degree);

}