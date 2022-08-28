#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <chrono>
#include "def.h"
namespace dx_engine {
	class logger {
		std::chrono::system_clock::time_point _startup_count;
		//std::ofstream ofs;
		FILE* fp;
		std::string filename = "Log.txt";
		bool flag = true;
		bool original = false;
	public:
		logger();
		~logger();
		int init();

		void set(bool output_flag ,bool use_original = false, const std::string& name = "Log.txt");
		void add(const std::string& str);
		void exception(const std::string& str);
		void critical(const std::string& str);
		void error(const std::string& str);
		void warn(const std::string& str);
		void info(const std::string& str);
		void debug(const std::string& str);

		bool use_original() const;
	};
}