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
#include "details.h"
#include "draw_param.h"
#include "point.h"
#include "vector.h"
#include "color.h"
#include "pallet.h"
#include "text.h"
#include "shape.h"
#include "texture.h"
#include "scene.h"
#include "device.h"



namespace dx_engine {
	

	class file final{

	};

	std::vector<std::string> split(const std::string& str, const std::string& splt);

	constexpr double degree(double radian);
	constexpr double radian(double degree);

	constexpr float degree_f(float radian);
	constexpr float radian_f(float degree);

	extern detail::_system system;
	extern detail::_window window;

}
