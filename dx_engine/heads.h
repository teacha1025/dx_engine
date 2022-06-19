#pragma once
#include <DxLib.h>

#include "point.h"

namespace dx_engine {
	namespace detail {
		class _system {
		private:

		public:
			bool update();
			~_system();
		};

		class _window {
		private:
			point<UINT> _size = {1280, 960};
		public:
			void size(const point<UINT>& size);
			point<UINT> size() const;
		};
	}

	extern detail::_system system;
	extern detail::_window window;
}