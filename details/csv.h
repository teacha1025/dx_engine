#pragma once
#include <string>
#include <vector>
#include "def.h"
#include "point.h"


namespace dx_engine {
	class csv {
	private:
		std::string name = "";
		std::vector<std::vector<std::string>> data;
		point<uint> _size;
	public:
		csv(const std::string& path, char split = ',');
		std::string at(const point<uint>& position) const;
		point<uint> size() const;
	};
}