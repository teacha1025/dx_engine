#pragma once
#include <functional>
#include "def.h"
#include "details.h"
#include "shape.h"
#include "text.h"

namespace dx_engine {
	namespace gui {
		template<class shape = rect>
		class clickable_object {
		private:

		protected:
			enum class cursor_info_t {
				none,
				hover,
				pressed
			}cursor_info;
		public:

		};

		template<class shape = rect>
		class button : public clickable_object<shape>{
		private:

		protected:

		public:

		};
	}
}