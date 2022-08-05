#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "def.h"

namespace dx_engine {
	namespace detail {
		class _file {
			std::unordered_map < std::string, std::string> data;
			std::vector<std::string> filelist;
			bool use_archive = false;
			void t_analyze();
			//friend melon_core;
		public:
			void load(const std::string& path);

			std::string get(const std::string& path);
			bool contain(const std::string& path);

			bool is_use() const;

			std::string operator [] (const std::string& path);
		};
	}
}