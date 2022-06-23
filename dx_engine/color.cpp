#include "DxLib.h"
#include "dx_engine.h"

namespace dx_engine {
	unsigned int color::to_int() const {
		return GetColor(r, g, b);
	}
}