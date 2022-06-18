#include "DxLib.h"
#include "dx_engine.h"

namespace dx_engine {
    namespace detail {
        bool _system::update() {
            return ProcessMessage() == 0 && ScreenFlip() == 0 && ClearDrawScreen() == 0;
        }
    }

    detail::_system system;
}