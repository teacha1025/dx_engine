#pragma once
#include "device_base.h"
namespace dx_engine {
	namespace detail {
		class _mouse : public input_base {
		public:
			_mouse(const unsigned int Code);
			_mouse() {}
			void update(const int& input);
		};
	}
}