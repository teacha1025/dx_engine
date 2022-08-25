#include <DxLib.h>
#include "../details/heads.h"

extern void init();
extern int main();
namespace dx_engine {
	extern logger log;
}
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	_set_se_translator([](unsigned int code, _EXCEPTION_POINTERS* ep) -> void {
		throw std::exception(std::to_string(code).c_str());
		});
	try{
		auto x = std::chrono::system_clock::now();
		init();
		auto y = std::chrono::system_clock::now();
		auto a = std::chrono::system_clock::now();
		dx_engine::log.init();
		auto b = std::chrono::system_clock::now();
		auto d = std::chrono::duration_cast<std::chrono::microseconds>(b - a);
		auto f = std::chrono::duration_cast<std::chrono::microseconds>(y - x);
		dx_engine::log.add(std::format("b-a:{}, y-x:{}", d.count(), f.count()));

		dx_engine::window.init();

		if (DxLib_Init() == -1) {
			dx_engine::log.critical("DxLib‚Ì‰Šú‰»‚É¸”s");
			return -1;
		}

		SetDrawScreen(DX_SCREEN_BACK);
		dx_engine::log.info("DxLib‚Ì‰Šú‰»Š®—¹");
		dx_engine::console.init(dx_engine::window.size());

		auto ret = main();
		dx_engine::log.info("I—¹");
		return 0;
	}
	catch (std::exception e) {
		dx_engine::log.exception(e.what());
		return -1;
	}
}