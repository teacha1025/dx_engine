#include "DxLib.h"
#include "../details/heads.h"

namespace dx_engine {
	unsigned int color::to_int() const {
		return GetColor(SCAST(int, r), SCAST(int, g), SCAST(int, b));
	}
}