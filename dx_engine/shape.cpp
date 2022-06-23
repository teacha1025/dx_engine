#include "DxLib.h"
#include "dx_engine.h"

namespace dx_engine {
	namespace detail {
		shape& shape::centered(const point<float>& center) {
			_center = center;
			return *this;
		}
		shape& shape::rotateed(float angle) {
			_angle = angle;
			return *this;
		}
		shape& shape::colored(const color& color) {
			_color = color;
			return *this;
		}
		shape& shape::blend(dx_engine::blend mode, int param) {
			_blend = mode;
			_blendparam = param;
			return *this;
		}
		shape& shape::at(const point<float>& position) {
			_position = position;
			return *this;
		}

		point<float> shape::position() const {
			return _position;
		}

		void shape::move(const point<float>& value) {
			_position += value;
		}
	}
}