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
		init();
		dx_engine::log.init();

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
	catch (...) {
		dx_engine::log.exception("unknown");
		return -1;
	}
}