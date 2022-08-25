#include "dx_engine.h"

using namespace dx_engine;

define N = 60.0;

void init() {
	dx_engine::log.set(true, true);
	window.fullscreen(false);
	window.size({ 1280,960 });
	window.background(pallet::lightskyblue);
	window.title("TEST");
	window.extends(systems.monitor_size().x / 1920.0f);
	//file.load("resource.dat");

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
	
	while (systems.update()) {
		window.title(std::format("Memory:{:.2f} MB / {:.2f} GB  Processor:{:#02.2f} %", systems.process_memory_info().PrivateUsage / (1024.0 * 1024.0), systems.memory_info().ullTotalPhys / (1024.0 * 1024.0 * 1024.0), systems.processor_usage()));
		
		console << std::format("{:5.2f}fps", systems.fps());
	}

	return 0;
}