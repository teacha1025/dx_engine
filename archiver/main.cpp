#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

#include "../details/encryption.h"
using namespace std;
namespace fs = filesystem;

int main() {
	cout << "dx_engine �A�[�J�C�u�쐬�\�t�g" << endl << endl;
	//cout << "�쐬���쐬���܂����H(y/n)�H:";
	//string s;
	//cin >> s;
	if (/*s == "yes" || s == "y"*/true) {

		std::ofstream fout;
		fs::path path;
		string ext;
		string header, data;
		cout << "�A�[�J�C�u�t�@�C���̊g���q�����:";
		cin >> ext;
		cout << "�A�[�J�C�u����t�H���_�����:";
		cin >> path;
		fout.open(path.string() + "." + ext, std::ios::out | std::ios::binary | std::ios::trunc);
		header.clear(); header.shrink_to_fit();
		data.clear(); data.shrink_to_fit();

		if (!fout) {
			cout << "�G���[:�t�@�C�����������߂܂���" << endl;
		}
		else {
			auto e = fs::recursive_directory_iterator(path);
			for (auto f : e) {
				if (fs::status(f.path()).type() == fs::file_type::directory) continue;
				string fname = f.path().generic_string(), size = std::to_string(fs::file_size(f.path()));
				ifstream idata;
				idata.open(fname, std::ios::binary);
				if (!idata) {
					cout << endl << "\t" << fname << "�̓X�L�b�v����܂���";
					continue;
				}

				cout << endl << "\t" << fname << "\t:" << (int)fs::status(f.path()).type() << "\t" << size << " B";

				stringstream d;
				d << idata.rdbuf();
				header += std::to_string(d.str().size()) + (char)'\"' + fname + (char)'\"';
				data += d.str();
			}
			cout << endl << endl;
			cout << "�t�@�C�� " << path.string() + "." + ext << " ���쐬���܂���" << endl;

			auto dt = header + (char)'@' + data;
			dt = MELON_ENCRYPT::encode(dt);

			string pressed;
			int ps = MELON_LZSS::LZSS_Encode(dt.data(), (int)dt.size(), NULL);
			pressed.resize(ps);
			MELON_LZSS::LZSS_Encode(dt.data(), (int)dt.size(), pressed.data());

			fout << pressed;
		}
	}
	else {
		/*string fname;
		cout << "Enter path:";
		cin >> fname;
		ifstream idata;
		idata.open(fname, std::ios::binary);
		if (!idata) {
			cout << endl << "\t" << fname << "���J���܂���" << endl;
		}
		else {
			stringstream data;
			data << idata.rdbuf();
			auto dt = data.str();

			string pln;

			int ps = MELON_LZSS::LZSS_Decode(dt.data(), NULL);
			pln.resize(ps);
			MELON_LZSS::LZSS_Decode(dt.data(), pln.data());

			pln = MELON_ENCRYPT::decode(pln);
			cout << "���(y/n)�H:";
			string s;
			cin >> s;
			if (s == "yes" || s == "y") {
				string head, body;
				auto atpos = pln.find((char)'@');
				cout << "@:" << atpos << endl;
				head = pln.substr(0, atpos);
				body = pln.substr(atpos + 1, pln.size() - 1);
				cout << "header:\n" << head << endl << endl;
				cout << "body:\n" << body << endl;
			}
			else {
				ofstream fout;
				fout.open(fname + "_declypt" + ".txt", std::ios::out | std::ios::binary | std::ios::trunc);
				if (!fout) {
					cout << "�t�@�C���J���Ȃ�" << endl;
				}
				else {
					fout << pln;
				}
			}
		}*/
	}

	system("pause");
	return 0;
}