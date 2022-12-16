#pragma once
#include <string>
#include <format>
#include <vector>
#include <numbers>
#include <memory>
#include <map>
#include <functional>
#include <cassert>
#include <DxLib.h>

#include "def.h"
#include "exception.h"
#include "logger.h"
#include "details.h"
#include "console.h"
#include "draw_param.h"
#include "point.h"
#include "vector.h"
#include "color.h"
#include "pallet.h"
#include "text.h"
#include "shape.h"
#include "file.h"
#include "texture.h"
#include "scene.h"
#include "device.h"
#include "step.h"
#include "range.h"
#include "coroutines.h"
#include "clock.h"
#include "audio.h"
#include "animation.h"
#include "event.h"
#include "collision.h"
#include "gui.h"
#include "functions.h"
#include "transition.h"
#include "csv.h"
#include "random.h"
#include "thread.h"
//#include "script.h"


namespace dx_engine {
	extern detail::_system systems;
	extern detail::_window window;
	extern detail::_console console;
	extern detail::_file file;
	extern detail::random_core rnd_core;
	extern logger log;
}
