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
			/// �t�H���_�̓ǂݍ���
			/// </summary>
			/// <param name="path">�t�H���_�̃p�X</param>
			void load(const std::string& path);

			/// <summary>
			/// �t�@�C���̃f�[�^�̎擾
			/// </summary>
			/// <param name="path">�t�@�C���̃p�X</param>
			/// <param name="reload">�t�@�C���̍ēǂݍ��݂����邩(�f�t�H���g�ł�false)</param>
			/// <returns>�t�@�C���̃f�[�^</returns>
			std::string get(const std::string& path, bool reload = false);
			/// <summary>
			/// �t�@�C�����܂܂�Ă��邩��T������
			/// </summary>
			/// <param name="path">�t�@�C���̃p�X</param>
			/// <returns>�܂܂�Ă��邩</returns>
			bool contain(const std::string& path);

			/// <summary>
			/// �A�[�J�C�u���g�p���Ă��邩���擾
			/// </summary>
			/// <returns>�g�p���Ă��邩</returns>
			bool is_use() const;

			/// <summary>
			/// �t�@�C���f�[�^���擾 get�֐��Ɠ��l
			/// </summary>
			/// <param name="path">�t�@�C���̃p�X</param>
			/// <returns>�t�@�C���̃f�[�^</returns>
			std::string operator [] (const std::string& path);
		};
	}
	extern detail::_file file;

	namespace file_io {
		/// <summary>
		/// �t�@�C���������o��
		/// </summary>
		/// <param name="path">�t�@�C���̃p�X</param>
		/// <param name="data">�����o���f�[�^</param>
		/// <param name="mode">�����o�����[�h</param>
		void export_file(const std::string& path, const std::string& data, std::ios::ios_base::openmode mode = std::ios::trunc);

		//template <class T, class Archive>
		//concept seriarize = requires(T & data, Archive & archive) {
		//	data.serialize(archive);
		//};

		/// <summary>
		/// �t�@�C�����o�C�i���Ƃ��ď����o��
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="path"></param>
		/// <param name="data"></param>
		/// <param name="encrypt"></param>
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