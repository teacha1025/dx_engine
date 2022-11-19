#include "../details/console.h"
#include "../details/shape.h"

namespace dx_engine {
	namespace detail {
		constexpr uint h = 16;
		void _console::init(const point<uint>& windowsize) {
			cr = cl = pallet::white;
			f.set_font("メイリオ", h, 1u, font_type::anti_aliasing);
			list.reserve(1 + h / windowsize.y);
			r_list.reserve(1 + h / windowsize.y);
		}

		void _console::update(const point<uint>& windowsize) {
			if (!flag) return;
			int i = 0;
			static rect rc;
			point<uint> p;
			for (auto&& t : list) {
				if (t.text == "") {
					i++;
					continue;
				}
				f = t.text;
				auto size = f.size();
				p = { 0, i * size.y };
				if (p.y >= windowsize.y) break;
				rc.resize(size);
				rc.at(p).centered({ 0,0 }).blend(blend::alpha, 127).colored(pallet::black).draw();
				f.centered({ 0,0 }).colored(t._color).at(p).draw();
				i++;
			}
			i = 0;
			for (auto&& t : r_list) {
				if (t.text == "") {
					i++;
					continue;
				}
				f = t.text;
				auto size = f.size();
				p = { windowsize.x, i * size.y };
				if (p.y >= windowsize.y) break;
				rc.resize(size);
				rc.at(p).centered({ size.x,0 }).blend(blend::alpha, 127).colored(pallet::black).draw();
				f.centered({ size.x,0 }).colored(t._color).at(p).draw();
				i++;
			}

			clear();
		}
		void _console::set(bool flg) {
			flag = flg;
		}
		void _console::clear() {
			list.clear();

			r_list.clear();
		}

	}
	detail::_console console;
}