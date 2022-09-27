#include "DxLib.h"
#include "../details/details.h"
#include "../details/logger.h"

namespace dx_engine {
	extern logger log;
	namespace detail {
		point<uint> window_top_pos = { 0,0 };
		void _window::size(const point<UINT>& size) {
			_size = size;
		}

		void _window::title(const std::string& title) {
			_title = title;

			SetWindowTextDX(_title.c_str());
		}

		point<UINT> _window::size() const {
			return _size;
		}

		void _window::background(const color& bg) {
			this->bg = bg;
		}

		float _window::extends() const {
			return _rate;
		}

		void _window::extends(float rate) {
			_rate = rate;
		}

		bool _window::fullscreen() const {
			return _fullscreen;
		}

		void _window::fullscreen(bool flag, fullscreen_type type) {
			_fullscreen = flag;
			_screentype = type;
		}

		void _window::init2() {
			if (_fullscreen) {
					_mainscreen = MakeScreen(_size.x, _size.y);
					if (_mainscreen <= 0) {
						log.error("mainscreen is invalid.");
					}
					SetDrawScreen(_mainscreen);
			}
			else {
				SetDrawScreen(DX_SCREEN_BACK);
			}
			SetBackgroundColor(SCAST(int, bg.r), SCAST(int, bg.g), SCAST(int, bg.b));
		}
		void _window::init() {
			
			if (_fullscreen) {
				auto DisplayNum = GetDisplayNum();
				int IsPrimary, RectX = 0, RectY = 0;
				for (int i = 0; i < DisplayNum; i++) {
					GetDisplayInfo(i, &RectX, &RectY, &_monitor_size.x, &_monitor_size.y, &IsPrimary);
					if (IsPrimary == TRUE)
					{
						break;
					}
				}
				if (_monitor_size.x / (float)_size.x >= _monitor_size.y / (float)_size.y) {// 描画画面の比率より横に長いか同じ場合
					_letterbox_size.y = 0;
					_letterbox_size.x = (_monitor_size.x - (_monitor_size.y * _size.x / _size.y)) / 2;
				}
				else {// 描画画面の比率より縦に長い場合
					_letterbox_size.x = 0;
					_letterbox_size.y = (_monitor_size.y - (_monitor_size.x * _size.y / _size.x)) / 2;
				}
				switch (_screentype) {
				case fullscreen_type::fullscreen_dotbydot:
				case fullscreen_type::borderless_dotbydot: {
					window_top_pos = (_monitor_size - _size) / 2;
					DrawRotaGraph(_monitor_size.x / 2, _monitor_size.y / 2, _rate, 0.0f, _mainscreen, FALSE, FALSE);
					break;
				}
				case fullscreen_type::fullscreen_full: 
				case fullscreen_type::borderless_full: {
					window_top_pos = _letterbox_size;
					break;
				}
				case fullscreen_type::fullscreen_flexible: 
				case fullscreen_type::borderless_flexible: {
					window_top_pos = {0,0};
					DrawExtendGraph(0, 0, _monitor_size.x, _monitor_size.y, _mainscreen, FALSE);
					break;
				}
				}
				
				SetWindowPosition(RectX, RectY);
				if (_screentype == fullscreen_type::fullscreen_dotbydot || _screentype == fullscreen_type::fullscreen_full || _screentype == fullscreen_type::fullscreen_flexible) {
					//SetGraphMode(_size.x, _size.y, 32);
					ChangeWindowMode(FALSE);
				}
				else {
					ChangeWindowMode(TRUE);
					SetWindowStyleMode(1);
				}
				SetGraphMode(_monitor_size.x, _monitor_size.y, 32);
				/*switch (_screentype) {
				case fullscreen_type::borderless_dotbydot: {

					break;
				}
				case fullscreen_type::borderless_full: {

					break;
				}
				case fullscreen_type::borderless_flexible: {

					break;
				}
				case fullscreen_type::fullscreen_dotbydot: {

					break;
				}
				case fullscreen_type::fullscreen_full: {

					break;
				}
				case fullscreen_type::fullscreen_flexible: {

					break;
				}
				}*/
			}
			else {
				SetGraphMode(_size.x, _size.y, 32);
				SetWindowSize((int)(_size.x * _rate), (int)(_size.y * _rate));
				ChangeWindowMode(TRUE);
				SetDrawScreen(DX_SCREEN_BACK);
			}
		}


		bool _window::update() {
			bool f;
			if (_fullscreen) {
				
				switch (_screentype) {
				case fullscreen_type::borderless_dotbydot: {
					SetDrawScreen(DX_SCREEN_BACK);
					ClearDrawScreen();
					DrawBox(0, 0, _monitor_size.x, _monitor_size.y, 0, TRUE);
					DrawRotaGraph(_monitor_size.x / 2, _monitor_size.y / 2, _rate, 0.0f, _mainscreen, FALSE, FALSE);
					SetDrawScreen(_mainscreen);
					break;
				}
				case fullscreen_type::borderless_full: {
					SetDrawScreen(DX_SCREEN_BACK);
					ClearDrawScreen();
					DrawBox(0, 0, _monitor_size.x, _monitor_size.y, 0, TRUE);
					DrawExtendGraph(_letterbox_size.x, _letterbox_size.y, _monitor_size.x - _letterbox_size.x, _monitor_size.y - _letterbox_size.y, _mainscreen, FALSE);
					SetDrawScreen(_mainscreen);
					break;
				}
				case fullscreen_type::borderless_flexible: {
					SetDrawScreen(DX_SCREEN_BACK);
					ClearDrawScreen();
					DrawBox(0, 0, _monitor_size.x, _monitor_size.y, 0, TRUE);
					DrawExtendGraph(0, 0, _monitor_size.x, _monitor_size.y, _mainscreen, FALSE);
					SetDrawScreen(_mainscreen);
					break;
				}
				case fullscreen_type::fullscreen_dotbydot: {
					SetDrawScreen(DX_SCREEN_BACK);
					ClearDrawScreen();
					DrawBox(0, 0, _monitor_size.x, _monitor_size.y, 0, TRUE);
					DrawRotaGraph(_monitor_size.x / 2, _monitor_size.y / 2, _rate, 0.0f, _mainscreen, FALSE, FALSE);
					SetDrawScreen(_mainscreen);
					break;
				}
				case fullscreen_type::fullscreen_full: {
					SetDrawScreen(DX_SCREEN_BACK);
					ClearDrawScreen();
					DrawBox(0, 0, _monitor_size.x, _monitor_size.y, 0, TRUE);
					DrawExtendGraph(_letterbox_size.x, _letterbox_size.y, _monitor_size.x - _letterbox_size.x, _monitor_size.y - _letterbox_size.y, _mainscreen, FALSE);
					SetDrawScreen(_mainscreen);
					break;
				}
				case fullscreen_type::fullscreen_flexible: {
					SetDrawScreen(DX_SCREEN_BACK);
					ClearDrawScreen();
					DrawBox(0, 0, _monitor_size.x, _monitor_size.y, 0, TRUE);
					DrawExtendGraph(0, 0, _monitor_size.x, _monitor_size.y, _mainscreen, FALSE);
					SetDrawScreen(_mainscreen);
					break;
				}
				}
			}
			f = !ScreenFlip();
			ClearDrawScreen();
			return f;
		}
	}

	detail::_window window;
}