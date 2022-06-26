#include "dx_engine.h"

using namespace dx_engine;

void init() {
    ChangeWindowMode(TRUE);
    dx_engine::window.size({ 1280,960 });
    dx_engine::window.background(pallet::lightskyblue);
    dx_engine::window.title("TEST");
}

class testscene : public scene<> {
private:

public:
    testscene() = default;
    testscene SCENE_CONSTRUCTOR;

    virtual void draw() override {
        rect({ 32,32 }).at(window.size() / 2).colored(pallet::red).draw();
    }
};

int Main() {
    text sceneid, fps;
    sceneid.set_font("メイリオ", 20u, 1u, font_type::edged_anti_aliasing);
    fps.set_font("メイリオ", 20u, 1u, font_type::edged_anti_aliasing);

    texture t("test2.bmp", {4,3});


    scene_manager<> scnmng;
    scnmng.add<testscene>(0);

    scnmng.set(0);
    
    while (dx_engine::system.update()) {
        fps = std::format("{:2.2f}", dx_engine::system.fps());
        sceneid = std::format("scene:{}", scnmng.get_current_scene_id());
        fps.colored(pallet::white).centered({fps.size().x,0}).at({1280,0}).draw();
        sceneid.at({0,0}).colored(pallet::white).draw();
        
        t[4].extended(5.0).blend(blend::none, 255).centered({0,0}).at(window.size() / 2).draw();

        scnmng.update();
    }

    return 0;
}