#include <format>
#include <chrono>
#include "DxLib.h"
#include "../details/def.h"
#include "../details/details.h"
#include "../details/console.h"
#include "../details/thread.h"

#pragma comment(lib, "pdh.lib")

namespace chrono = std::chrono;

namespace dx_engine {
	namespace detail {
		_system::_system() {
			_handle = GetCurrentProcess();
			_pid = GetProcessId(_handle);
			
			GetSystemInfo(&_sysinfo);

			MEMORYSTATUSEX msex = { sizeof(MEMORYSTATUSEX) };
			GlobalMemoryStatusEx(&msex);
			_memory_statu = msex;

			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
				PROCESS_VM_READ,
				FALSE, _pid);

			HMODULE hMod;
			DWORD cbNeeded;
			TCHAR szProcessName[MAX_PATH];

			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
				&cbNeeded))
			{
				GetModuleBaseName(hProcess, hMod, szProcessName,
					sizeof(szProcessName) / sizeof(TCHAR));
			}

			PdhOpenQuery(NULL, 0, &_hquery);

			auto path = std::format("\\Process(test)\\% Processor Time");

			PdhAddCounter(_hquery, path.c_str(), 0, &_hcounter);
			PdhCollectQueryData(_hquery);
		}

		bool _system::update() {
			constexpr auto get_clock_nano_now = []() {return chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now().time_since_epoch()).count(); };
			constexpr auto get_clock_micro_now = []() {return chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch()).count(); };
			constexpr auto get_clock_milli_now = []() {return chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count(); };
			{
				static auto old = get_clock_milli_now(), now = get_clock_milli_now();
				now = get_clock_milli_now();
				delta_msec = now - old;
				old = now;
			}

			{
				static auto old = get_clock_milli_now(), now = get_clock_milli_now();
				static int cnt = 0;

				now = get_clock_milli_now();
				auto d = now - old;
				if (d >= 0.25 / MILLI) {
					_fps = cnt / SCAST(float, d) / MILLI_F;
					old = now;
					cnt = 0;


					PdhCollectQueryData(_hquery);
					PdhGetFormattedCounterValue(_hcounter, PDH_FMT_DOUBLE, NULL, &_fmt);
					_cpu_usage = _fmt.doubleValue / _sysinfo.dwNumberOfProcessors;
				}
				cnt++;
			}
			{
				//const auto p = (double)_max_fps + 0.2 * (1.0 / 120.0 * (double)_max_fps + 0.45);
				//double waitTime = ((((double)cnt / MICRO - (double)(now - old) * p) / p)) * MILLI;
				////double waitTime = (cnt * MILLI / _max_fps - (double)(now - old)) * 1;
				//if (waitTime > 0) {
				//	WaitTimer((int)waitTime);
				//}
				if (_max_fps != HUGE_VALF) {

					static auto old_h = get_clock_nano_now(), now_h = get_clock_nano_now();
					//static int cnt_h = 0;
					//auto _d = now_h - old_h;
					//if (_d >= 0.25 / MILLI) {
					//	old_h = now_h;
					//	cnt_h = 0;
					//}
					//_d = now_h - old_h;
					//cnt_h++;
					//const auto p = (double)_max_fps + 0.2 * (1.0 / 120.0 * (double)_max_fps + 0.45);
					//double waitTime = ((((double)cnt_h / MILLI - (double)(_d) * p) / p)) * MILLI;
					////double waitTime = (cnt_h * MILLI / _max_fps - (double)(_d)) * 1;
					//if (waitTime > 0) {
					//	WaitTimer((int)waitTime);
					//}
					const auto sleep = [&](long long t) {
						const auto count = get_clock_nano_now() + t;

						while (count > get_clock_nano_now()) {

						}
					};
					const long long INTERVAL = (long long)(1.0 / NANO / (double)_max_fps);
					now_h = get_clock_nano_now();
					auto term = INTERVAL - (now_h - old_h);

					if (term > 0) {//‘Ò‚Â‚×‚«ŽžŠÔ‚¾‚¯‘Ò‚Â
						//Sleep(term / 1000000);
						sleep(term*2);
					}
					old_h = now_h;
				}
			}

			keyboard.update();
			mouse.update();

			thread_manager.update();

			console.set(debug_mode);
			if (debug_mode) {
				console.update(window.size());
			}

			_total_frame++;

			return ProcessMessage() == 0 && window.update();
		}

		float _system::delta_sec() const {
			return delta_msec / MILLI_F;
		}
		double _system::delta_sec_d() const {
			return delta_msec / MILLI;
		}

		ULONGLONG _system::total_frame() const {
			return _total_frame;
		}

		float _system::fps() const {
			return _fps;
		}

		void _system::vsync(bool flag) {
			SetWaitVSyncFlag(flag ? TRUE : FALSE);
		}

		void _system::max_fps(float value) {
//#pragma message("max_fps : this function wont work") 
			_max_fps = value;
		}

		PROCESS_MEMORY_COUNTERS_EX _system::process_memory_info() const{
			PROCESS_MEMORY_COUNTERS_EX pmc{};
			BOOL isSuccess = GetProcessMemoryInfo(
				_handle,
				(PROCESS_MEMORY_COUNTERS*)&pmc,
				sizeof(pmc));
			//CloseHandle(handle);
			
			return pmc;
		}

		MEMORYSTATUSEX _system::memory_info() const {
			return _memory_statu;
		}

		double _system::processor_usage() const {
			
			return _cpu_usage;
		}

		_system::~_system() {
			DxLib_End();
			CloseHandle(_handle);
			PdhCloseQuery(_hquery);
		}

		SYSTEM_INFO _system::system_info() const {
			return _sysinfo;
		}

		point<uint> _system::monitor_size() const {
			static uint x = (uint)GetSystemMetrics(SM_CXSCREEN);
			static uint y = (uint)GetSystemMetrics(SM_CYSCREEN);

			return { x, y };
		}
	}

	detail::_system systems;
}