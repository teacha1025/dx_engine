#include <DxLib.h>
#include "heads.h"

extern void Init();
extern int Main();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Init();

    if (DxLib_Init() == -1) {
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    auto ret = Main();

    return 0;
}