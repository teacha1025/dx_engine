#include "DxLib.h"
#include "../details/details.h"

namespace dx_engine {
	namespace detail {
		void _window::size(const point<UINT>& size) {
			_size = size;
		}

		void _window::title(const std::string& title) {
			_title = title;
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

		void _window::fullscreen(bool flag) {
			_fullscreen = flag;
		}

		void _window::init() {
			SetGraphMode(_size.x, _size.y, 32);
			SetBackgroundColor(SCAST(int, bg.r), SCAST(int, bg.g), SCAST(int, bg.b));
			SetWindowSize((int)(_size.x * _rate), (int)(_size.y * _rate));
			ChangeWindowMode(_fullscreen ? FALSE : TRUE);
			SetWindowTextDX(_title.c_str());
		}

	}

	detail::_window window;
}