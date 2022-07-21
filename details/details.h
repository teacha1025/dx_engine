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
#include "text.h"
#include "device.h"

namespace dx_engine {
	namespace detail {
		struct dbg {
			std::string text;
			color _color;
			dbg(std::string_view tex, const color& c) {
				text = tex;
				this->_color = c;
			}
		};

		template<typename T>
		concept Number = std::integral<T> || std::floating_point<T>;

		class _console {
			std::vector<dbg> list, r_list;
			text f;
			color cl = pallet::white, cr = pallet::white;
			bool flag = false;
		public:
			void init(const point<uint>& windowsize);
			void update(const point<uint>& windowsize);
			void clear();
			void set(bool flg);

			_console& operator << (const std::string& str) {
				if (!flag) return *this;
				list.push_back(dbg(str, cl));
				return *this;
			}
			_console& operator >> (const std::string& str) {
				if (!flag) return *this;
				r_list.push_back(dbg(str, cr));
				return *this;
			}

			_console& operator << (const char str[]) {
				if (!flag) return *this;
				list.push_back(dbg(std::string(str), cl));
				return *this;
			}
			_console& operator >> (const char str[]) {
				if (!flag) return *this;
				r_list.push_back(dbg(std::string(str), cr));
				return *this;
			}
			_console& operator << (const color& c) {
				if (!flag) return *this;
				cl = c;
				return *this;
			}
			_console& operator >> (const color& c) {
				if (!flag) return *this;
				cr = c;
				return *this;
			}

			_console& operator << (bool b) {
				if (!flag) return *this;
				list.push_back(dbg(b ? "true" : "false", cl));
				return *this;
			}
			template <Number t>
			_console& operator >> (bool b) {
				if (!flag) return *this;
				r_list.push_back(dbg(b ? "true" : "false", cr));
				return *this;
			}

			template <Number t>
			_console& operator << (const point<t>& p) {
				if (!flag) return *this;
				list.push_back(dbg(p.to_string(), cl));
				return *this;
			}
			template <Number t>
			_console& operator >> (const point<t>& p) {
				if (!flag) return *this;
				r_list.push_back(dbg(p.to_string(), cr));
				return *this;
			}

			template <Number t>
			_console& operator << (t v) {
				if (!flag) return *this;
				list.push_back(dbg(std::to_string(v), cl));
				return *this;
			}
			template <Number t>
			_console& operator >> (t v) {
				if (!flag) return *this;
				r_list.push_back(dbg(std::to_string(v), cr));
				return *this;
			}
		};

		class _system final {
		private:
			ULONGLONG delta_msec = 0;
			float _fps;

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

		class shape {
		protected:
			point<float> _position{}, _center{};
			float _angle = 0;
			float _thick = 1.0f;
			color _color;
			blend _blend = blend::alpha;
			byte _blendparam = 255;
			bool _fill_flag = true;
		public:
			virtual shape& centered(const dx_engine::point<float>& center);
			virtual shape& rotateed(float angle);
			virtual shape& colored(const color& color);
			virtual shape& blend(dx_engine::blend mode, range<0, 255> param);
			virtual shape& at(const dx_engine::point<float>& position);
			virtual shape& fill(bool flag);
			virtual shape& thick(float thick);

			virtual point<float> position() const;

			virtual void move(const dx_engine::point<float>& value);

			virtual void draw() = 0;
		};
	}
}