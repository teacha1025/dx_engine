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
			float _fps = 0, _max_fps = HUGE_VALF;
			bool _vsync = true;

			HANDLE _handle;
			DWORD _pid;

			SYSTEM_INFO _sysinfo;

			MEMORYSTATUSEX _memory_statu;

			PDH_HQUERY _hquery;
			PDH_HCOUNTER _hcounter;
			PDH_FMT_COUNTERVALUE _fmt{};

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

		enum class fullscreen_type {
			borderless_dotbydot,	//ボーダーレスウィンドウ　DOTbyDOT
			borderless_full,		//ボーダーレスウィンドウ　最大表示
			borderless_flexible,	//ボーダーレスウィンドウ　画面全体に引き延ばす
			fullscreen_dotbydot,	//フルスクリーン　DOTbyDOT
			fullscreen_full,		//フルスクリーン　最大表示
			fullscreen_flexible,	//フルスクリーン　画面全体に引き延ばす
		};

		class _window final {
		private:
			point<uint> _size = { 1280, 960 };
			bool _fullscreen = false, _vsync = false;
			float _rate;
			std::string _title;
			color bg;
			fullscreen_type _screentype;

			int _mainscreen;
			point<int> _monitor_size, _letterbox_size;
		public:
			void background(const color& bg);
			void title(const std::string& title);

			void fullscreen(bool flag, fullscreen_type type = fullscreen_type::borderless_dotbydot);
			bool fullscreen() const;

			void size(const point<uint>& size);
			point<uint> size() const;

			void extends(float rate);
			float extends() const;

			bool update();

			void init();
			void init2();
		};

		
	}

	extern detail::_system systems;
	extern detail::_window window;
	
}