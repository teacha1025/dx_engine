#pragma once
#include <string>
#include <stdexcept>
#include <format>

namespace dx_engine {
	class exception : public std::runtime_error {
	public:
		/// <summary>
		/// 例外の作成
		/// </summary>
		/// <param name="func">関数名</param>
		/// <param name="msg">メッセージ</param>
		exception(const char* func, const std::string& msg)
			: runtime_error(std::format("{}  func:{}", msg,func)) {

		}
	};
}

#ifndef EXCEPT
#define EXCEPT(msg) exception(__FUNCTION__,msg)
#endif