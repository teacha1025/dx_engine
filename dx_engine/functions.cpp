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

	
}