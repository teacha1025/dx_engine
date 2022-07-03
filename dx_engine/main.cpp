#include <DxLib.h>
#include "heads.h"

extern void init();
extern int main();


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	init();

	if (DxLib_Init() == -1) {
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	dx_engine::console.init(dx_engine::window.size());

	auto ret = main();

	return 0;
}