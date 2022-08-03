#pragma once
#include <functional>
#include "def.h"
#include "details.h"
#include "shape.h"
#include "collision.h"
#include "text.h"

namespace dx_engine {
	namespace gui {
		template<class shape = rect>
		class clickable_object {
		private:
			bool _down_onshape;
		protected:
			shape button_object;
			enum class cursor_info_t {
				none,
				hover,
				pressed
			}cursor_info;

			virtual bool released_onshape() {

			}
		public:

		};

		template<class shape = rect>
		class button : public clickable_object<shape>{
		private:

		protected:

		public:
			bool operator () () {
				return this->released_onshape();
			}
		};
	}
}