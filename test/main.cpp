#include "dx_engine.h"

using namespace dx_engine;

void Init() {
    ChangeWindowMode(TRUE);
    dx_engine::window.size({ 1280,960 });
}

int Main() {
    dx_engine::point<int> size(280, 160);
    rect r({280,160});
    circle c(32);
    //std::string s;
    string ss, fps;
    ss.set_font("メイリオ", 20u, 1u, font_type::anti_aliasing);
    fps.set_font("メイリオ", 20u, 1u, font_type::anti_aliasing);

    texture t("test2.bmp", {4,3});

    ss = "Hello!!";
    
    while (dx_engine::system.update()) {
        r.colored(pallet::white).at({640,480}).colored({255,255,255}).draw();
        c.colored(pallet::skyblue).at(dx_engine::system.mouse.position()).draw();

        ss.colored(pallet::white).at({0,0}).draw();
        fps = std::format("{:2.2f}", dx_engine::system.fps());
        fps.colored(pallet::white).at({ 0,24 }).draw();
        string("aa").at({0,60}).colored(pallet::white).draw();
        
        t[4].extended(5.0).blend(blend::none, 255).centered({0,0}).at(window.size() / 2).draw();
    }

    return 0;
}