#include "dx_engine.h"

using namespace dx_engine;

void Init() {
    ChangeWindowMode(TRUE);
    dx_engine::window.size({ 1280,960 });
}

int Main() {
    dx_engine::point<int> size(280, 160);
    rect r({280,160});
    std::string s;
    string ss;

    ss = "aa";
    
    while (dx_engine::system.update()) {
        //DrawBox(500, 400, 780, 560, GetColor(255, 255, 255), TRUE);
        r.at({ 640,480 }).colored({ 255,255,255 }).draw();
    }

    return 0;
}