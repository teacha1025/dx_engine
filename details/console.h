#pragma once
#include <string>
#include <vector>
#include "def.h"
#include "draw_param.h"
#include "point.h"
#include "vector.h"
#include "color.h"
#include "pallet.h"
#include "text.h"
#include "device.h"
namespace dx_engine {
	namespace detail {
		struct dbg {
			std::string text;
			color _color;
			dbg(std::string_view tex, const color& c) {
				text = tex;
				this->_color = c;
			}
		};

		class _console {
			std::vector<dbg> list, r_list;
			text f;
			color cl = pallet::white, cr = pallet::white;
			bool flag = false;
		public:
			void init(const point<uint>& windowsize);
			void update(const point<uint>& windowsize);
			void clear();
			void set(bool flg);

			_console& operator << (const std::string& str) {
				if (!flag) return *this;
				list.push_back(dbg(str, cl));
				return *this;
			}
			_console& operator >> (const std::string& str) {
				if (!flag) return *this;
				r_list.push_back(dbg(str, cr));
				return *this;
			}

			_console& operator << (const char str[]) {
				if (!flag) return *this;
				list.push_back(dbg(std::string(str), cl));
				return *this;
			}
			_console& operator >> (const char str[]) {
				if (!flag) return *this;
				r_list.push_back(dbg(std::string(str), cr));
				return *this;
			}
			_console& operator << (const color& c) {
				if (!flag) return *this;
				cl = c;
				return *this;
			}
			_console& operator >> (const color& c) {
				if (!flag) return *this;
				cr = c;
				return *this;
			}

			_console& operator << (bool b) {
				if (!flag) return *this;
				list.push_back(dbg(b ? "true" : "false", cl));
				return *this;
			}
			template <Number t>
			_console& operator >> (bool b) {
				if (!flag) return *this;
				r_list.push_back(dbg(b ? "true" : "false", cr));
				return *this;
			}

			template <Number t>
			_console& operator << (const point<t>& p) {
				if (!flag) return *this;
				list.push_back(dbg(p.to_string(), cl));
				return *this;
			}
			template <Number t>
			_console& operator >> (const point<t>& p) {
				if (!flag) return *this;
				r_list.push_back(dbg(p.to_string(), cr));
				return *this;
			}

			template <Number t>
			_console& operator << (t v) {
				if (!flag) return *this;
				list.push_back(dbg(std::to_string(v), cl));
				return *this;
			}
			template <Number t>
			_console& operator >> (t v) {
				if (!flag) return *this;
				r_list.push_back(dbg(std::to_string(v), cr));
				return *this;
			}
		};

	}
	extern detail::_console console;
}