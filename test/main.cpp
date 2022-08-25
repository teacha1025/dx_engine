#include "dx_engine.h"

using namespace dx_engine;

define N = 60.0;

void init() {
	dx_engine::log.set(true, true);
	window.fullscreen(true);
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
	uint counter = 0;
public:
	SCENE_CONSTRUCTOR(testscene)

	virtual void init() override {
		counter = 0;
	}

	virtual void draw() override {
		rect({ 32,32 }).at({ counter % 1280,counter / 980 }).colored(pallet::red).draw();
		console << counter;
		console << std::format("scene:{}", id());
	}

	virtual void update() override {
		counter++;
		if (systems.keyboard.Num2.down()) {
			change_scene(2, 60, false);
		}
	}
};

class testscene2 : public scene<> {
private:
	uint counter = 0;
public:
	SCENE_CONSTRUCTOR(testscene2)

	virtual void init() override {
		counter = 0;
	}

	virtual void draw() override {
		rect({ 32,32 }).at({ counter % 1280,counter / 980 }).colored(pallet::green).draw();
		console << counter;
		console << std::format("scene:{}", id());
	}

	virtual void update() override {
		if (systems.keyboard.Num1.down()) {
			change_scene(1,40, true);
		}
		counter++;
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
	scene_manager scenemanager;
	scenemanager.add<testscene>(1);
	scenemanager.add<testscene2>(2);
	while (systems.update()) {
		window.title(std::format("Memory:{:.2f} MB / {:.2f} GB  Processor:{:#02.2f} %", systems.process_memory_info().PrivateUsage / (1024.0 * 1024.0), systems.memory_info().ullTotalPhys / (1024.0 * 1024.0 * 1024.0), systems.processor_usage()));
		
		console << std::format("{:5.2f}fps", systems.fps());

		scenemanager.update();
	}

	return 0;
}