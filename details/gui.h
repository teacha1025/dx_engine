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
			bool _down_onshape = false;
		protected:
			shape button_object;
			enum class cursor_info_t {
				none,
				hover,
				pressed
			}cursor_info;

			virtual bool released_onshape() {
				if (systems.mouse.Left.down()) {
					if (collision(systems.mouse.position(), button_object)) {
						_down_onshape = true;
					}
					else {
						false;
					}
					return false;
				}
				if (systems.mouse.Left.up()) {
					if (collision(systems.mouse.position(), button_object)) {
						return _down_onshape;
					}
					else {
						return false;
					}
				}
				return false;
			}
		public:

		};

		template<class shape = rect>
		class button : public clickable_object<shape>{
		private:

		protected:

		public:
			button(const shape& object) {
				this->button_object = object;
			}
			bool operator () () {
				this->button_object.draw();
				return this->released_onshape();
			}
		};
	}
}