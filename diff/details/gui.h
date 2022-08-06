#pragma once
#include <functional>
#include <unordered_map>
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
			using func_type = std::function<void(shape, text)>;
			bool enabled = true;
			shape button_object;
			enum class cursor_info_t {
				none,
				disabled,
				hover,
				pressed
			}cursor_info = cursor_info_t::none;
			std::unordered_map<cursor_info_t, func_type> function_list;
			text txt = "button";
			void set_info() {
				if (!enabled) {
					cursor_info = cursor_info_t::disabled;
					return;
				}
				if (collision(systems.mouse.position(), button_object)) {
					if (_down_onshape && systems.mouse.Left.press()) {
						cursor_info = cursor_info_t::pressed;
					}
					else {
						cursor_info = cursor_info_t::hover;
					}
				}
				else {
					cursor_info = cursor_info_t::none;
					_down_onshape = false;
				}
			}
			virtual bool released_onshape() {
				set_info();

				if (systems.mouse.Left.down()) {
					if (cursor_info != cursor_info_t::none && cursor_info != cursor_info_t::disabled) {
						_down_onshape = true;
					}
					else {
						false;
					}
					return false;
				}
				if (systems.mouse.Left.up()) {
					if (cursor_info != cursor_info_t::none && cursor_info != cursor_info_t::disabled) {
						if (_down_onshape) {
							_down_onshape = false;
							return true;
						}
					}
					else {
						return false;
					}
				}
				return false;
			}

			void init_funclist() {
				function_list.insert(std::make_pair(cursor_info_t::none, [](shape obj, text t) {obj.colored(pallet::white).draw(); t.colored(pallet::black).draw(); }));
				function_list.insert(std::make_pair(cursor_info_t::hover, [](shape obj, text t) {obj.colored(pallet::whitesmoke).draw(); t.colored(pallet::black).draw(); }));
				function_list.insert(std::make_pair(cursor_info_t::pressed, [](shape obj, text t) {obj.colored(pallet::gray).draw(); t.colored(pallet::white).draw(); }));
				function_list.insert(std::make_pair(cursor_info_t::disabled, [](shape obj, text t) {obj.colored(pallet::white).draw(); t.colored(pallet::lightgrey).draw(); }));
			}
		public:
			void at(point<double> position) {
				button_object.at(position);
			}
			void set_function_hovered(func_type f) {
				function_list.at(cursor_info_t::hover) = f;
			}
			void set_function_pressed(func_type f) {
				function_list.at(cursor_info_t::pressed) = f;
			}
			void set_function_normal(func_type f) {
				function_list.at(cursor_info_t::none) = f;
			}
			void enable(bool flag) {
				enabled = flag;
				set_info();
			}
			void set_text(const std::string& t) {
				txt = t;
			}
			void set_font(const std::string& fontname = "", dx_engine::uint size = 16, dx_engine::uint thick = 1, dx_engine::font_type type = font_type::normal, uint edgesize = -1, bool italic = false) {
				txt.set_font(fontname, size, thick, type, edgesize, italic);
			}
		};

		template<class shape = rect>
		class button : public clickable_object<shape>{
		private:

		protected:

		public:
			button(const shape& object, const std::string& t, bool enabled = true) {
				this->button_object = object;
				this->set_text(t);
				this->set_font("���S�V�b�N", 12u, 1u, font_type::anti_aliasing);
				this->txt.centered(this->txt.size() / 2.0).at(this->button_object.position());
				this->init_funclist();
				this->enable(enabled);
			}
			
			bool operator () () {
				this->txt.centered(this->txt.size() / 2.0).at(this->button_object.position());
				auto f = this->function_list.at(this->cursor_info); 
				f(this->button_object, this->txt);
				return this->released_onshape();
			}
		};
	}
}