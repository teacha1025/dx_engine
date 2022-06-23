#include "dx_engine.h"

using namespace dx_engine;

void Init() {
    ChangeWindowMode(TRUE);
    dx_engine::window.size({ 1280,960 });
}

int Main() {
    dx_engine::point<int> size(280, 160);
    rect r;

    while (dx_engine::system.update()) {
        DrawBox(500, 400, 780, 560, GetColor(255, 255, 255), TRUE);
        
    }

    return 0;
}