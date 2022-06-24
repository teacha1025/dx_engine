#include "DxLib.h"
#include "dx_engine.h"

namespace dx_engine {
    namespace detail {
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
                    _fps = cnt / static_cast<float>(d) * 1000;
                    old = now;
                    cnt = 0;
                }
                cnt++;
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

        _system::~_system() {
            DxLib_End();
        }
    }

    detail::_system system;
}