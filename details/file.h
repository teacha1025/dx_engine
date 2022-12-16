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
			/// <summary>
			/// フォルダの読み込み
			/// </summary>
			/// <param name="path">フォルダのパス</param>
			void load(const std::string& path);

			/// <summary>
			/// ファイルのデータの取得
			/// </summary>
			/// <param name="path">ファイルのパス</param>
			/// <param name="reload">ファイルの再読み込みをするか(デフォルトではfalse)</param>
			/// <returns>ファイルのデータ</returns>
			std::string get(const std::string& path, bool reload = false);
			/// <summary>
			/// ファイルが含まれているかを探索する
			/// </summary>
			/// <param name="path">ファイルのパス</param>
			/// <returns>含まれているか</returns>
			bool contain(const std::string& path);

			/// <summary>
			/// アーカイブを使用しているかを取得
			/// </summary>
			/// <returns>使用しているか</returns>
			bool is_use() const;

			/// <summary>
			/// ファイルデータを取得 get関数と同様
			/// </summary>
			/// <param name="path">ファイルのパス</param>
			/// <returns>ファイルのデータ</returns>
			std::string operator [] (const std::string& path);
		};
	}
	extern detail::_file file;

	namespace file_io {
		/// <summary>
		/// ファイルを書き出す
		/// </summary>
		/// <param name="path">ファイルのパス</param>
		/// <param name="data">書き出すデータ</param>
		/// <param name="mode">書き出すモード</param>
		void export_file(const std::string& path, const std::string& data, std::ios::ios_base::openmode mode = std::ios::trunc);

		class serializable {
		public:
			virtual void serialize() = 0;
		};

		template<class T>
		concept serializable_c = requires (T & s) {
			s.serialize();
		};

		/// <summary>
		/// ファイルをバイナリとして書き出す
		/// </summary>
		/// <typeparam name="T">serialize関数を含むデータのクラス</typeparam>
		/// <param name="path">書き出すファイルへのパス</param>
		/// <param name="data">データ</param>
		/// <param name="encrypt">暗号化するか</param>
		template <serializable_c T>
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

		/// <summary>
		/// ファイルをバイナリとして読み込む
		/// </summary>
		/// <typeparam name="T">serialize関数を含むデータのクラス</typeparam>
		/// <param name="path">読み込むファイルへのパス</param>
		/// <param name="data">データ</param>
		/// <param name="encrypt">暗号化されているか</param>
		template <serializable_c T>
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

		/// <summary>
		/// ファイルをjsonとして書き出す
		/// </summary>
		/// <typeparam name="T">serialize関数を含むデータのクラス</typeparam>
		/// <param name="path">書き出すファイルへのパス</param>
		/// <param name="data">データ</param>
		/// <param name="encrypt">暗号化するか</param>
		template <serializable_c T>
		void export_json(const std::string& path, T& data, bool encrypt = true) {
			std::stringstream ss;
			std::string exports;
			cereal::JSONOutputArchive archive(ss);
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

		/// <summary>
		/// ファイルをjsonとして読み込む
		/// </summary>
		/// <typeparam name="T">serialize関数を含むデータのクラス</typeparam>
		/// <param name="path">読み込むファイルへのパス</param>
		/// <param name="data">データ</param>
		/// <param name="encrypt">暗号化されているか</param>
		template <serializable_c T>
		void import_json(const std::string& path, T& data, bool encrypt = true) {
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
			cereal::JSONInputArchive archive(ss);
			archive(data);
		}
	}
}