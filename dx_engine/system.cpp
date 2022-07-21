#include "DxLib.h"
#include "../details/heads.h"

#pragma comment(lib, "pdh.lib")

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
			{
				static auto old = GetTickCount64(), now = GetTickCount64();
				now = GetTickCount64();
				delta_msec = now - old;
				old = now;
			}

			{
				static auto old = GetTickCount64(), now = GetTickCount64();
				static int cnt = 0;

				now = GetTickCount64();
				auto d = now - old;
				if (d >= 0.25 * 1000) {
					_fps = cnt / SCAST(float, d) * 1000;
					old = now;
					cnt = 0;

					
					PdhCollectQueryData(_hquery);
					PdhGetFormattedCounterValue(_hcounter, PDH_FMT_DOUBLE, NULL, &_fmt);
					_cpu_usage = _fmt.doubleValue / _sysinfo.dwNumberOfProcessors;
				}
				cnt++;
			}

			keyboard.update();
			mouse.update();

			console.set(debug_mode);
			if (debug_mode) {
				console.update(window.size());
			}

			return ProcessMessage() == 0 && ScreenFlip() == 0 && ClearDrawScreen() == 0;
		}

		float _system::delta_sec() const {
			return delta_msec / 1000.0f;
		}
		double _system::delta_sec_d() const {
			return delta_msec / 1000.0;
		}

		float _system::fps() const {
			return _fps;
		}

		PROCESS_MEMORY_COUNTERS_EX _system::process_memory_info() const{
			PROCESS_MEMORY_COUNTERS_EX pmc;
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