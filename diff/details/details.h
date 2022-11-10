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

	enum class fullscreen_type {
		borderless_dotbydot,	//ボーダーレスウィンドウ　DOTbyDOT
		borderless_full,		//ボーダーレスウィンドウ　最大表示
		borderless_flexible,	//ボーダーレスウィンドウ　画面全体に引き延ばす
		fullscreen_dotbydot,	//フルスクリーン　DOTbyDOT
		fullscreen_full,		//フルスクリーン　最大表示
		fullscreen_flexible,	//フルスクリーン　画面全体に引き延ばす
	};
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
			/// <summary>
			/// デバッグモードかどうか (デフォルトはDebugモードではtrue, Releaseモードではfalse)
			/// </summary>
			bool debug_mode = true;
#else
			/// <summary>
			/// デバッグモードかどうか (デフォルトはDebugモードではtrue, Releaseモードではfalse)
			/// </summary>
			bool debug_mode = false;
#endif
			_system();

			/// <summary>
			/// キーボード
			/// </summary>
			device::keyboard keyboard;

			/// <summary>
			/// マウス
			/// </summary>
			device::mouse mouse;

			/// <summary>
			/// エンジンのアップデート　毎フレーム呼び出す
			/// </summary>
			/// <returns>フレームを続けるか</returns>
			bool update();

			/// <summary>
			/// 前フレームとの差
			/// </summary>
			/// <returns>前フレームから何秒経ったか(float)</returns>
			float delta_sec() const;

			/// <summary>
			/// 前フレームとの差
			/// </summary>
			/// <returns>前フレームから何秒経ったか(double)</returns>
			double delta_sec_d() const;

			/// <summary>
			/// フレームレートの計算
			/// </summary>
			/// <returns>現在のフレームレート</returns>
			float fps() const;

			/// <summary>
			/// 垂直同期の設定
			/// </summary>
			/// <param name="flag">垂直同期を使用するか</param>
			void vsync(bool flag);

			/// <summary>
			/// フレームレートの最大値を設定　現在無効
			/// </summary>
			/// <param name="value">最大値</param>
			void max_fps(float value);

			/// <summary>
			/// プロセスメモリの情報を取得
			/// </summary>
			/// <returns>プロセスメモリの情報</returns>
			PROCESS_MEMORY_COUNTERS_EX process_memory_info() const;

			/// <summary>
			/// メモリの情報を取得
			/// </summary>
			/// <returns>メモリの情報</returns>
			MEMORYSTATUSEX memory_info() const;

			/// <summary>
			/// CPU使用量の計算
			/// </summary>
			/// <returns>CPU使用量</returns>
			double processor_usage() const;

			/// <summary>
			/// システムの情報を取得
			/// </summary>
			/// <returns>システムの情報</returns>
			SYSTEM_INFO system_info() const;

			/// <summary>
			/// モニターサイズの取得
			/// </summary>
			/// <returns>モニターサイズ</returns>
			point<uint> monitor_size() const;

			~_system();
		};

		

		class _window final {
		private:
			point<uint> _size = { 1280, 960 };
			bool _fullscreen = false, _vsync = false;
			float _rate = 1.0f;
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

			int back_screen() const;
		};

		
	}

	extern detail::_system systems;
	extern detail::_window window;
	
}