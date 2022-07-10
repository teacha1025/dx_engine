#include "dx_engine.h"

using namespace dx_engine;

void init() {
	ChangeWindowMode(TRUE);
	window.size({ 1280,960 });
	window.background(pallet::lightskyblue);
	window.title("TEST");
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
		testtext.at({ 0,160 }).draw();
	}

	virtual void update() override {
		updater.next();
	}
};

int main() {
	text memory_disp, fps;
	memory_disp.set_font("メイリオ", 10u, 1u, font_type::edge);
	fps.set_font("メイリオ", 16u, 1u, font_type::anti_aliasing);

	texture t("test_2.bmp", {4,3});
	audio pan("test.wav", false);
	audio music("07 G Free.mp3", false);

	scene_manager<> scnmng;
	scnmng.add<testscene>(0);

	scnmng.set(0);
	//music.play();
	while (systems.update()) {
		
		fps = std::format("{:2.2f} fps", systems.fps());
		fps.colored(pallet::white).centered({ fps.size().x,0 }).at({ 1280,0 }).draw();
		memory_disp = std::format("Memory:{:.2f} MB / {:.2f} GB  Processor:{:#02.2f} %", systems.process_memory_info().PrivateUsage / (1024.0 * 1024.0), systems.memory_info().ullTotalPhys / (1024.0 * 1024.0 * 1024.0), systems.processor_usage());
		memory_disp.at({0,0}).colored(pallet::white).draw();
		
		t[4].extended(5.0).blend(blend::none, 255).centered({0,0}).at(window.size() / 2).draw();
		console << true;
		scnmng.update();
		auto p = systems.mouse.position().x * 2.0 / 1280.0 - 1.0f;
		console << p;
		console << systems.mouse.position();
		music.pan(p);
		if (systems.keyboard.Return.count() % 16 == 0) {
			music.play();
			console << "play";
			
		}
	}

	return 0;
}