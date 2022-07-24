#include "DxLib.h"
#include "../details/details.h"

namespace dx_engine {
	namespace detail {
		void _window::size(const point<UINT>& size) {
			_size = size;
			SetGraphMode(size.x, size.y, 32);
		}

		void _window::title(const std::string& title) {
			SetWindowTextDX(title.c_str());
		}

		point<UINT> _window::size() const {
			return _size;
		}

		void _window::background(const color& bg) {
			SetBackgroundColor(SCAST(int, bg.r), SCAST(int, bg.g), SCAST(int, bg.b));
		}

		float _window::extends() const {
			return _rate;
		}

		void _window::extends(float rate) {
			SetWindowSize((int)(_size.x * rate), (int)(_size.y * rate));
		}

		bool _window::fullscreen() const {
			return _fullscreen;
		}

		void _window::fullscreen(bool flag) {
			ChangeWindowMode(flag ? FALSE : TRUE);
			_fullscreen = flag;
		}

	}

	detail::_window window;
}