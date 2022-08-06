#include "dx_engine.h"

using namespace dx_engine;

define N = 60.0;

void init() {
	window.fullscreen(false);
	window.size({ 1280,960 });
	window.background(pallet::lightskyblue);
	window.title("TEST");
	window.extends(1.0);
	file.load("Resource.dat");

	//systems.vsync(false);
	//systems.max_fps(N);
}

class testscene : public scene<> {
private:
	text testtext;
	uint counter = 0;
	task updater{ c_update()};
	clock::stopwatch sw;
	uint i = 0;
public:
	SCENE_CONSTRUCTOR(testscene)

	virtual void init() override {
		//sw.restart();
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
		//updater.next();
		/*if (systems.keyboard.Return.down()) {
			sw.restart();
			i = 0;
		}
		auto v = i++ / N - sw.get_sec();
		console << v << v / sw.get_sec();*/

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

class evt : public::dx_engine::event {
private:
	uint _time;
public:
	evt(uint time) :_time(time) {}

	bool update(uint count) override {
		dx_engine::console >> "event" >> count;
		return count < _time;
	}
};

class evt2 : public::dx_engine::event {
private:
	uint _time;
public:
	evt2(uint time) :_time(time) {}

	bool update(uint count) override {
		dx_engine::console >> "event2" >> count;
		return count < _time;
	}
};

struct save_struct {
	int a, b, c, d;
	float e, f, g;
	std::string h;

	template<class Archive>
	void serialize(Archive& archive) {
		archive(a, b, c, d, e, f, g, h);
	}
};

int main() {
	text memory_disp, fps, mpos;
	memory_disp.set_font("メイリオ", 10u, 1u, font_type::edge);
	fps.set_font("メイリオ", 16u, 1u, font_type::anti_aliasing);
	mpos.set_font("メイリオ", 16u, 1u, font_type::anti_aliasing);

	line l;
	l.thick(1).at({ {128, 128}, {920, 648}, {640, 64} });

	rect r({240,240});
	r.centered({ 32,32 }).rotateed(1*PI/4.0).at({0, 0});
	rect r2({ 120,20 });
	r2.centered({ 32,32 }).rotateed(0.8 * PI / 4.0).at({ 250, 480 });

	circle c(64);
	c.centered({ -20, -20 }).at({ 640, 480 });
	circle c2(28);
	c2.centered({ -20, -20 }).at({ 640, 480 });

	color cl = pallet::blue;

	circle btn_obj(40);
	btn_obj.at(window.size()/2).colored(pallet::white);
	
	texture tex("Resource/test.jpg");
	texture texp("Resource/player.png", { 8,3 });

	audio pan("Resource/test.wav", false);

	gui::button<circle> btn(btn_obj, systems.debug_mode ? "release" : "debug", true);
	//btn.set_function_hovered([](circle r, text t) {r.colored(pallet::lightgreen).draw(); t.draw(); });

	save_struct sv, sva;
	sv.a = sv.b = sv.c = sv.d = 0;
	sv.e = sv.f = sv.g = 1.0f;
	sv.h = "name";

	file_io::export_binary("save.dat", sv, true);
	file_io::import_binary("save.dat", sva, true);

	while (systems.update()) {
		window.title(std::format("Memory:{:.2f} MB / {:.2f} GB  Processor:{:#02.2f} %", systems.process_memory_info().PrivateUsage / (1024.0 * 1024.0), systems.memory_info().ullTotalPhys / (1024.0 * 1024.0 * 1024.0), systems.processor_usage()));
		if (systems.keyboard.F3.down() || btn()) {
			//btn.at({GetRand(1280 - 32) + 64,GetRand(960 - 32) + 64 });
			systems.debug_mode ^= 1;
			//btn.set_text(systems.debug_mode ? "release" : "debug");
			pan.play();
		}

		console >> std::format("{:2.2f} fps", systems.fps());
		if (systems.debug_mode) {
			//memory_disp = std::format("Memory:{:.2f} MB / {:.2f} GB  Processor:{:#02.2f} %", systems.process_memory_info().PrivateUsage / (1024.0 * 1024.0), systems.memory_info().ullTotalPhys / (1024.0 * 1024.0 * 1024.0), systems.processor_usage());
			//memory_disp.at({ 0,0 }).colored(pallet::white).draw();
		}
		console << systems.mouse.position();

		//tex.at({ 128,128 }).centered({ 0,0 }).trans(false).draw();
		//texp[5].at({ 256, 256 }).draw();
	}

	return 0;
}