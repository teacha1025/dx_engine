#pragma once
#include <vector>
#include <string>
#include "def.h"

namespace dx_engine {
	std::vector<std::string> split(const std::string& str, const std::string& splt);

	double degree(double radian);
	double radian(double degree);

	float degree_f(float radian);
	float radian_f(float degree);

	uint factorial(uint n);
	uint binomial(uint n, uint k);
}