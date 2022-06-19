#include "DxLib.h"
#include "dx_engine.h"

namespace dx_engine {
    namespace detail {
        bool _system::update() {
            return ProcessMessage() == 0 && ScreenFlip() == 0 && ClearDrawScreen() == 0;
        }

        _system::~_system() {
            DxLib_End();
        }
    }

    detail::_system system;
}