#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <Pdh.h>
#include <string>
#include <vector>
#include "def.h"
#include "draw_param.h"
#include "point.h"
#include "vector.h"
#include "color.h"
#include "pallet.h"
#include "device.h"
#include "range.h"

namespace dx_engine {
	namespace detail {

		class _system final {
		private:
			ULONGLONG delta_msec = 0;
			float _fps, _max_fps = HUGE_VALF;
			bool _vsync = true;

			HANDLE _handle;
			DWORD _pid;

			SYSTEM_INFO _sysinfo;

			MEMORYSTATUSEX _memory_statu;

			PDH_HQUERY _hquery;
			PDH_HCOUNTER _hcounter;
			PDH_FMT_COUNTERVALUE _fmt;

			double _cpu_usage = 0;
		public:
#ifdef _DEBUG
			bool debug_mode = true;
#else
			bool debug_mode = false;
#endif
			_system();

			device::keyboard keyboard;
			device::mouse mouse;
			bool update();
			float delta_sec() const;
			double delta_sec_d() const;
			float fps() const;
			void vsync(bool flag);
			void max_fps(float value);

			PROCESS_MEMORY_COUNTERS_EX process_memory_info() const;
			MEMORYSTATUSEX memory_info() const;

			double processor_usage() const;
			SYSTEM_INFO system_info() const;

			point<uint> monitor_size() const;

			~_system();
		};

		class _window final {
		private:
			point<uint> _size = { 1280, 960 };
			bool _fullscreen = false, _vsync = false;
			float _rate;
		public:
			void background(const color& bg);
			void title(const std::string& title);

			void fullscreen(bool flag);
			bool fullscreen() const;

			void size(const point<uint>& size);
			point<uint> size() const;

			void extends(float rate);
			float extends() const;

			
		};

		class draw_object {
		protected:
			blend _blend = blend::alpha;
			byte _blendparam = 255;
			filter _filter = filter::nearest;
		public:
			virtual void draw() = 0;
		};

		class shape : public draw_object{
		protected:
			point<float> _position{}, _center{};
			float _angle = 0;
			float _thick = 1.0f;
			color _color;
			
			bool _fill_flag = true;
		public:
			virtual shape& centered(const dx_engine::point<float>& center);
			virtual shape& rotateed(float angle);
			virtual shape& colored(const color& color);
			virtual shape& blend(dx_engine::blend mode, range<0, 255> param);
			virtual shape& filter(filter mode);
			virtual shape& at(const dx_engine::point<float>& position);
			virtual shape& fill(bool flag);
			virtual shape& thick(float thick);

			virtual point<float> position() const;

			virtual void move(const dx_engine::point<float>& value);
		};
	}

	extern detail::_system systems;
	extern detail::_window window;
	
}