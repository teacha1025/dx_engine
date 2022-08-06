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

			std::string get(const std::string& path);
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
		void export_binary(const std::string& path, T& data) {
			std::stringstream ss;
			cereal::BinaryOutputArchive archive(ss);
			archive(data);

			auto dt = ss.str();
			dt = MELON_ENCRYPT::encode(dt);

			std::string pressed;
			int ps = MELON_LZSS::LZSS_Encode(dt.data(), (int)dt.size(), NULL);
			pressed.resize(ps);
			MELON_LZSS::LZSS_Encode(dt.data(), (int)dt.size(), pressed.data());
			export_file(path, pressed);
		}

		template <class T>
		void import_binary(const std::string& path, T& data) {
			std::stringstream ss;

			std::string pln;

			int ps = MELON_LZSS::LZSS_Decode(file[path].data(), NULL);
			pln.resize(ps);
			MELON_LZSS::LZSS_Decode(file[path].data(), pln.data());

			pln = MELON_ENCRYPT::decode(pln);
			ss << pln;

			cereal::BinaryInputArchive archive(ss);
			archive(data);
		}
	}
}