#include <DxLib.h>
#include "heads.h"

extern void init();
extern int Main();


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    init();

    if (DxLib_Init() == -1) {
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    auto ret = Main();

    return 0;
}