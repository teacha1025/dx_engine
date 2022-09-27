#include <DxLib.h>
#include <future>
#include "../details/heads.h"

extern void init();
extern int main();
namespace dx_engine {
	extern logger log;
}
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
#ifndef DISABLE_SEH_DETECT
	_set_se_translator([](unsigned int code, _EXCEPTION_POINTERS* ep) -> void {
		std::string exp = "";
		switch (code){
		case EXCEPTION_FLT_DIVIDE_BY_ZERO:
		case EXCEPTION_INT_DIVIDE_BY_ZERO:
			exp = "0による除算";
			break;
		case EXCEPTION_ACCESS_VIOLATION:
			exp = "アクセス違反";
			break;
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
			exp = "範囲外アクセス";
			break;
		case EXCEPTION_INT_OVERFLOW:
		case EXCEPTION_FLT_OVERFLOW:
			exp = "オーバーフロー";
			break;
		case EXCEPTION_FLT_UNDERFLOW:
			exp = "アンダーフロー";
			break;
		case EXCEPTION_INVALID_HANDLE:
			exp = "無効なハンドル";
			break;
		case EXCEPTION_STACK_OVERFLOW:
			exp = "スタックオーバーフロー";
			break;
		case 0xE06D7363:
			exp = "C++ Exception";
			break;
		default:
			exp = "unknown";
			break;
		}
		throw std::exception(std::format("SEH code:0x{:X}  {}", code, exp).c_str());
		});
#endif
	try{
		init();
		dx_engine::log.init();

		dx_engine::window.init();

		if (DxLib_Init() == -1) {
			dx_engine::log.critical("DxLibの初期化に失敗");
			return -1;
		}
		dx_engine::window.init2();
		dx_engine::log.info("DxLibの初期化完了");
		dx_engine::console.init(dx_engine::window.size());

		auto main_thread = std::async(std::launch::async, main);
		auto ret = main_thread.get();
		dx_engine::log.info(std::format("終了 コード:{}", ret));
		return 0;
	}
	catch (std::exception e) {
		dx_engine::log.exception(e.what());
		return -1;
	}
	catch (...) {
		dx_engine::log.exception("unknown");
		return -1;
	}
}