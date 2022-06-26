#include "DxLib.h"
#include "heads.h"

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
            //_background = bg;
            SetBackgroundColor(SCAST(int, bg.r), SCAST(int, bg.g), SCAST(int, bg.b));
        }

    }

    detail::_window window;
}