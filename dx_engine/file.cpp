#define NOMINMAX
#include <string>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <vector>
#include <thread>

#include "../details/def.h"
#include "../details/file.h"
#include "../details/text.h"

#include "../details/encryption.h"

namespace dx_engine {
	namespace detail {

		void _file::load(const std::string& path) {
			std::ifstream idata;
			idata.open(path, std::ios::binary);
			if (!idata) {
				//log.error("ファイル " + path + " の読み込みに失敗");
				return;
			}

			try {
				std::stringstream data;
				data << idata.rdbuf();
				auto dt = data.str();
				std::string pln;
				int ps = MELON_LZSS::LZSS_Decode(dt.data(), NULL);
				pln.resize(ps);
				MELON_LZSS::LZSS_Decode(dt.data(), pln.data());

				pln = MELON_ENCRYPT::decode(pln);

				std::string head, body;
				auto atpos = pln.find((wchar_t)'@');
				head = pln.substr(0, atpos);
				body = pln.substr(atpos + 1, pln.size() - 1);

				auto h = split(head, '\"', false);
				int c = 0;
				for (int i = 0; i < h.size(); i += 2) {
					int size = std::stoi(h.at(i));
					auto sb = body.substr(c, c + size);
					c += size;
					this->data.insert(std::make_pair(h.at(i + 1), sb));
				}
				use_archive = true;
			}
			catch (...) {
				//log.error("不正なファイルです");
			}
		}

		void _file::t_analyze() {
			if (filelist.size() == 0) return;
			std::vector<std::thread> th;

			auto fnc = [&](const std::string& path) {
				std::ifstream idata;
				idata.open(path, std::ios::binary);
				if (!idata) {
					//log.error("�t�@�C�� " + path + " �̓ǂݍ��݂Ɏ��s");
					return;
				}

				try {
					std::stringstream data;
					data << idata.rdbuf();
					auto dt = data.str();
					std::string pln;
					int ps = MELON_LZSS::LZSS_Decode(dt.data(), NULL);
					pln.resize(ps);
					MELON_LZSS::LZSS_Decode(dt.data(), pln.data());

					pln = MELON_ENCRYPT::decode(pln);

					std::string head, body;
					auto atpos = pln.find((wchar_t)'@');
					head = pln.substr(0, atpos);
					body = pln.substr(atpos + 1, pln.size() - 1);

					auto h = split(head, '\"', false);
					int c = 0;
					for (int i = 0; i < h.size(); i += 2) {
						int size = std::stoi(h[i]);
						auto sb = body.substr(c, c + size);
						c += size;
						this->data.insert(std::make_pair(h[i + 1], sb));
					}
					use_archive = true;
				}
				catch (...) {
					//log.error("�s���ȃt�@�C���ł�");
				}
			};

			for (auto&& pth : filelist) {
				th.push_back(std::thread(fnc, pth));
			}
			for (auto&& t : th) {
				t.join();
			}
		}

		std::string _file::get(const std::string& path) {
			if (!data.contains(path)) {
				std::ifstream idata;
				idata.open(path, std::ios::binary);
				if (!idata) {
					//log.error("\t�t�@�C�� " + path + " �̓ǂݍ��݂Ɏ��s");
					return std::string();
				}
				std::stringstream sdata;
				sdata << idata.rdbuf();
				data.insert(std::make_pair(path, sdata.str()));
			}

			return data[path];
		}

		bool _file::contain(const std::string& path) {

			if (!data.contains(path)) {
				std::ifstream idata;
				idata.open(path, std::ios::binary);
				if (!idata) {
					if (!std::filesystem::exists({ path })) {
						//log.error("\t�t�@�C�� " + path + " �͑��݂��܂���");
					}
					else {
						//log.error("�t�@�C�� " + path + " �͗��p�ł��܂���");
					}
					return false;
				}

				std::stringstream sdata;
				sdata << idata.rdbuf();
				data.insert(std::make_pair(path, sdata.str()));
			}
			return true;
		}

		bool _file::is_use() const {
			return use_archive;
		}

		std::string _file::operator [] (const std::string& path) {
			return get(path);
		}
	}

	void export_file(const std::string& path, const std::string& data, std::ios::ios_base::openmode mode) {
		std::ofstream ofs(path, mode);
		if (!ofs)
		{
			//std::cout << "ファイルが開けませんでした。" << std::endl;
			return;
		}

		ofs << data;
	}

	detail::_file file;
}