#include "DxLib.h"
#include "dx_engine.h"

namespace dx_engine {
    namespace detail {
        void _window::size(const point<UINT>& size) {
            _size = size;
            SetGraphMode(size.x, size.y, 32);
        }

        point<UINT> _window::size() const {
            return _size;
        }
    }

    detail::_window window;
}