#define NOMINMAX
#include<DxLib.h>
#include <stdlib.h>
#include <iomanip>
//#include <sstream>
#include <string>
#include <format>
//#include <fstream>
#include <chrono>
#include <Windows.h>
#include <system_error>
#include "../details/def.h"
#include "../details/logger.h"

namespace dx_engine {
	//std::ofstream logger::ofs;

	logger::logger() {
		_startup_count = std::chrono::system_clock::now();
	}
	logger::~logger() {
		if (!flag && original) return;
		/*if (ofs) {
			ofs.close();
		}*/
		if (fp != nullptr) {
			fclose(fp);
		}
	}
	int logger::init() {
		if (!flag) return 0;
		SetApplicationLogFileName(filename.c_str());
		if (original) { 
			SetOutApplicationLogValidFlag(TRUE);
			return 0;
		}
		SetOutApplicationLogValidFlag(FALSE);
		//namespace chrono = std::chrono;
		//chrono::local_seconds lt = chrono::zoned_seconds{ "Asia/Tokyo", chrono::floor<chrono::seconds>(chrono::system_clock::now()) }.get_local_time();

		auto e = fopen_s(&fp, filename.c_str(), "w");
		if (e != 0) {
			while (true) {
				OutputDebugString("ログファイルの作成に失敗");
				auto id = MessageBoxA(NULL, "ログファイルを作成できません。\nフォルダが書き込み禁止になってませんか？", "ログファイルの作成に失敗", MB_ABORTRETRYIGNORE | MB_ICONERROR);
				if (id == IDABORT) {
					return 1;
				}
				else if (id == IDRETRY || id == IDTRYAGAIN) {
					e = fopen_s(&fp, filename.c_str(), "w");
					if (e != 0) continue;
					else {
						//add("起動時刻 " + std::format("{:%Y/%m/%d %X}  Lib version: {:x}", lt, dx_engine::ENGINE));
						add(std::format("起動 Lib version: {}", dx_engine::ENGINE_S));
						return 0;
					}
				}
				else if (id == IDIGNORE) {
					flag = false;
					return 0;
				}
			}
		}
		else {
			//add(std::format("起動時刻 {:%Y/%m/%d %X}  Lib version: {}", lt, dx_engine::ENGINE_S));
			add(std::format("起動 Lib version: {}",dx_engine::ENGINE_S));
			return 0;
		}

		/*ofs = std::ofstream(filename);
		if (!ofs) {
			while (true) {
				OutputDebugString("ログファイルの作成に失敗");
				auto id = MessageBoxA(NULL, "ログファイルを作成できません。\nフォルダが書き込み禁止になってませんか？", "ログファイルの作成に失敗", MB_ABORTRETRYIGNORE | MB_ICONERROR);
				if (id == IDABORT) {
					return 1;
				}
				else if (id == IDRETRY || id == IDTRYAGAIN) {
					ofs = std::ofstream(filename);
					if (!ofs) continue;
					else {
						add("起動時刻 " + std::format("{:%Y/%m/%d %X}  Lib version: {:x}", lt, dx_engine::ENGINE));
						return 0;
					}
				}
				else if (id == IDIGNORE) {
					flag = false;
					return 0;
				}
			}
		}
		else {
			add("起動時刻 " + std::format("{:%Y/%m/%d %X}  Lib version: {}", lt, dx_engine::ENGINE_S));
			return 0;
		}*/
	}
	void logger::set(bool output_flag, bool use_original, const std::string& name) {
		filename = name;
		this->flag = output_flag;
		this->original = use_original;
	}
	void logger::add(const std::string& str) {
		if (original) {
			AppLogAdd(str.c_str());
		}
		else {
			static std::string log;
			auto t = std::chrono::system_clock::now();
			auto d = std::chrono::duration_cast<std::chrono::milliseconds>(t - _startup_count);
			log = std::format("[{}]\t{}\n", d.count(), str);
			OutputDebugString(log.c_str());
			if (!flag)return;
			if (fp == nullptr) {
				if (init() != 0) return;
			}
			//if (ofs) ofs << log;
			if (fp != nullptr) fprintf(fp, log.c_str());
		}
	}
	void logger::exception(const std::string& str) {
		add("Exception: " + str);
	}
	void logger::critical(const std::string& str) {
		add("Critical: " + str);
	}
	void logger::error(const std::string& str) {
		add("Error: " + str);
	}
	void logger::warn(const std::string& str) {
		add("Warning: " + str);
	}
	void logger::info(const std::string& str) {
		add("Info: " + str);
	}
	void logger::debug(const std::string& str) {
		add("Debug: " + str);
	}
	//void logger::result(CPRM(HRESULT) result) {
	//	switch (result) {
	//	case S_OK:
	//	{
	//		add(std::format("\t\tコード:{0:#x} {1}", (long)result, "成功"));
	//		break;
	//	}
	//	case E_ABORT:
	//	{
	//		add(std::format("\t\tコード:{0:#x} {1}", (long)result, "操作の中断"));
	//		break;
	//	}
	//	case E_ACCESSDENIED:
	//	{
	//		add(std::format("\t\tコード:{0:#x} {1}", (long)result, "アクセスの拒否"));
	//		break;
	//	}
	//	case E_FAIL:
	//	{
	//		add(std::format("\t\tコード:{0:#x} {1}", (long)result, "失敗"));
	//		break;
	//	}
	//	case E_HANDLE:
	//	{
	//		add(std::format("\t\tコード:{0:#x} {1}", (long)result, "無効なハンドル"));
	//		break;
	//	}
	//	case E_INVALIDARG:
	//	{
	//		add(std::format("\t\tコード:{0:#x} {1}", (long)result, "引数が無効"));
	//		break;
	//	}
	//	case E_NOINTERFACE:
	//	{
	//		add(std::format("\t\tコード:{0:#x} {1}", (long)result, "サポートされていないインターフェイス"));
	//		break;
	//	}
	//	case E_NOTIMPL:
	//	{
	//		add(std::format("\t\tコード:{0:#x} {1}", (long)result, "未実装"));
	//		break;
	//	}
	//	case E_OUTOFMEMORY:
	//	{
	//		add(std::format("\t\tコード:{0:#x} {1}", (long)result, "メモリ割り当てに失敗"));
	//		break;
	//	}
	//	case E_POINTER:
	//	{
	//		add(std::format("\t\tコード:{0:#x} {1}", (long)result, "無効なポインタ"));
	//		break;
	//	}
	//	case E_UNEXPECTED:
	//	{
	//		add(std::format("\t\tコード:{0:#x} {1}", (long)result, "予期しないエラー"));
	//		break;
	//	}
	//	default: {
	//		add(std::format("\t\tコード:{0:#x} {1}", (long)result, std::system_category().message(result)));
	//		break;
	//	}
	//	}
	//}
	bool logger::use_original() const {
		return original;
	}
	logger log;
}