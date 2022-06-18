#include "dx_engine.h"

int init() {
    ChangeWindowMode(TRUE);
    SetGraphMode(1280, 960, 32, 60);
    if (DxLib_Init() == -1) {
        return -1;
    }
    SetDrawScreen(DX_SCREEN_BACK);
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    if (init() == -1) {
        return -1;
    }

    while (dx_engine::system.update()) {
        DrawBox(500, 400, 780, 560, GetColor(255, 255, 255), TRUE);
    }

    DxLib_End();

    return 0;
}