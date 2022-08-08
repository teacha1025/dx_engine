#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "../details/file.h"
#include "../details/csv.h"
#include "../details/def.h"
#include "../details/point.h"
#include "../details/functions.h"
#include "../details/text.h"

namespace dx_engine {
	extern detail::_file file;
	csv::csv(const std::string& path, char spl) {
		if (!file.contain(path)) {
			_size = { 0u,0u };
			return;
		}
		name = path;
		auto source = file.get(path);
		data.resize(0);
		std::string destStr;
		for (auto c : source) {
			if (c == '\r') {
				c = '\n';
			}
			destStr += c;
		}
		destStr = replace_string(destStr, "\n\n", "\n");
		source = std::move(destStr);

		auto d = split(source, '\n', false);
		for (auto&& line : d) {
			auto s = split(line, spl, false);
			data.push_back(s);
		}

		_size = { data[0].size(), data.size() };
		return;
	}

	std::string csv::at(const point<uint>& position) const {
		if (_size == point<uint>{0u, 0u}) return ";";
		try {
			return data[position.y][position.x];
		}
		catch (...) {
			return "";
		}
	}

	point<uint> csv::size() const {
		return _size;
	}
}