#pragma once
#include <DxLib.h>

namespace dx_engine {
	namespace detail {
		class _system {
		private:

		public:
			bool update();
		};
	}

	extern detail::_system system;
}