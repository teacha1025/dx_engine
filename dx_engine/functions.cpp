#include <cmath>
#include <numbers>
#include <string>
#include <vector>
#include "../details/functions.h"

namespace dx_engine {
	std::vector<std::string> split(const std::string& source, const std::string& splt) {
		if (splt == "") return { source };
		std::vector<std::string> result;
		std::string tstr = source + splt;
		auto l = tstr.length(), sl = splt.length();
		std::string::size_type pos = 0, prev = 0;

		for (; pos < l && (pos = tstr.find(splt, pos)) != std::string::npos; prev = (pos += sl)) {
			result.emplace_back(tstr, prev, pos - prev);
		}
		return result;
	}

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
	constexpr double cexp_pow(double p, uint n)
	{
		double s = 1.0;

		for (uint k = 0; k < n; k++)
		{
			s *= p;
		}
		return s;
	}
	constexpr uint factorial(uint n) {
		uint r = 1;
		for (uint i = 2; i <= n; i++)
		{
			r *= i;
		}

		return r;
	}
	constexpr uint binomial(uint n, uint k) {
		return factorial(n) / (factorial(k) * factorial(n - k));
	}
	constexpr double bernsterin(uint n, uint i, double t) {
		return binomial(n, i) * cexp_pow(t, i) * cexp_pow(1 - t, n - i);
	}
}