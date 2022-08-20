#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>

#include "cereal/archives/binary.hpp"
#include "cereal/archives/portable_binary.hpp"
#include "cereal/archives/xml.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/types/map.hpp"
#include "cereal/types/string.hpp"
#include "encryption.h"
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

			std::string get(const std::string& path, bool reload = false);
			bool contain(const std::string& path);

			bool is_use() const;

			std::string operator [] (const std::string& path);
		};
	}
	extern detail::_file file;

	namespace file_io {
		void export_file(const std::string& path, const std::string& data, std::ios::ios_base::openmode mode = std::ios::trunc);

		//template <class T, class Archive>
		//concept seriarize = requires(T & data, Archive & archive) {
		//	data.serialize(archive);
		//};

		template <class T>
		void export_binary(const std::string& path, T& data, bool encrypt = true) {
			std::stringstream ss;
			std::string exports;
			cereal::BinaryOutputArchive archive(ss);
			archive(data);
			if (encrypt) {
				auto dt = ss.str();
				dt = MELON_ENCRYPT::encode(dt);

				int ps = MELON_LZSS::LZSS_Encode(dt.data(), (int)dt.size(), NULL);
				exports.resize(ps);
				MELON_LZSS::LZSS_Encode(dt.data(), (int)dt.size(), exports.data());
			}
			else {
				exports = ss.str();
			}
			export_file(path, exports);
		}

		template <class T>
		void import_binary(const std::string& path, T& data, bool encrypt = true) {
			std::stringstream ss;

			if (encrypt) {
				std::string pln;

				int ps = MELON_LZSS::LZSS_Decode(file[path].data(), NULL);
				pln.resize(ps);
				MELON_LZSS::LZSS_Decode(file[path].data(), pln.data());

				pln = MELON_ENCRYPT::decode(pln);
				ss << pln;
			}
			else {
				ss << file[path];
			}
			cereal::BinaryInputArchive archive(ss);
			archive(data);
		}
	}
}