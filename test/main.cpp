#include "dx_engine.h"

using namespace dx_engine;

void init() {
	window.fullscreen(false);
	window.size({ 1280,960 });
	window.background(pallet::lightskyblue);
	window.title("TEST");

	window.extends(1.0);
}

class testscene : public scene<> {
private:
	text testtext;
	uint counter = 0;
	task updater{ c_update()};
public:
	SCENE_CONSTRUCTOR(testscene)

	virtual void init() override {

	}

	task c_update() {
		uint i = 0;
		while (1) {
			testtext = i;
			co_yield coroutines::wait(60);
			i++;
		}
	}

	virtual void draw() override {
		rect({ 32,32 }).at(window.size() / 2).colored(pallet::red).draw();
		testtext.colored(pallet::red).at({0,160}).draw();
	}

	virtual void update() override {
		updater.next();

		if (systems.keyboard.Num2.down()) {
			change_scene(2);
		}
	}
};

class testscene2 : public scene<> {
private:
	text testtext;
	uint counter = 0;
	task updater{ c_update() };
public:
	SCENE_CONSTRUCTOR(testscene2)

	virtual void init() override {

	}

	task c_update() {
		uint i = 0;
		while (1) {
			testtext = i;
			co_yield coroutines::wait(60);
			i++;
		}
	}

	virtual void draw() override {
		//rect({ 32,32 }).at(window.size() / 2).colored(pallet::red).draw();
		circle(32).at(window.size() / 2.0f).colored(pallet::white).fill(false).draw();
		testtext.colored(pallet::green).at({0,160}).draw();
	}

	virtual void update() override {
		updater.next();

		if (systems.keyboard.Num1.down()) {
			change_scene(1,40);
		}
	}
};

int main() {
	text memory_disp, fps, mpos;
	memory_disp.set_font("メイリオ", 10u, 1u, font_type::edge);
	fps.set_font("メイリオ", 16u, 1u, font_type::anti_aliasing);
	mpos.set_font("メイリオ", 16u, 1u, font_type::anti_aliasing);

	//texture t("player.png", {8,3});
	animation anm("player.png", { 8,3 });
	anm.add(0, { 0,1,2,3,4,5,6,7 }, 5, true);
	anm.add(1, { 12,13,14,15 }, 5, true);
	anm.add(2, { 20,21,22,23 }, 5, true);
	anm.set(0);

	scene_manager<> scnmng;
	scnmng.add<testscene>(1);
	scnmng.add<testscene2>(2);

	scnmng.set(1);

	event_manager e;

	while (systems.update()) {

		if (systems.keyboard.F3.down()) {
			systems.debug_mode ^= 1;
		}

		fps = std::format("{:2.2f} fps", systems.fps());
		fps.colored(pallet::white).centered({ fps.size().x,0 }).at({ 1280,0 }).draw();
		memory_disp = std::format("Memory:{:.2f} MB / {:.2f} GB  Processor:{:#02.2f} %", systems.process_memory_info().PrivateUsage / (1024.0 * 1024.0), systems.memory_info().ullTotalPhys / (1024.0 * 1024.0 * 1024.0), systems.processor_usage());
		memory_disp.at({ 0,0 }).colored(pallet::white).draw();
		mpos = systems.mouse.position();
		mpos.at({ 0,20 }).colored(pallet::white).draw();

		
		console << std::format("scene : {}", scnmng.get_current_scene_id());
		console << std::format("monitor : {}", systems.monitor_size().to_string());

		if (systems.keyboard.Num8.down()) {
			anm.set(0);
		}
		else if (systems.keyboard.Num7.down()) {
			anm.set(1);
		}
		else if (systems.keyboard.Num9.down()) {
			anm.set(2);
		}

		if (systems.keyboard.Space.down()) {
			anm.pause();
		}
		if (systems.keyboard.Space.up()) {
			anm.resume();
		}
		anm.at(window.size() * 3.0 / 4.0).extended(2.0f).play();

		scnmng.update();
	}

	return 0;
}