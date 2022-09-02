#include <time.h>
#include "../details/gui.h"

namespace dx_engine {
	
	namespace gui {
		pulldown::pulldown(const std::vector<std::string>& elems, const point<int>& pos) {
			text t, arrow;
			t.set_font("ü‡ÉSÉVÉbÉN", 12u, 1u, font_type::anti_aliasing);
			uint id = 0;
			float w = 0, h = 12.0f + 4.0f;
			for (auto& elm : elems) {
				t = elm;
				auto x = t.size().x;
				 w = std::max(x, w);
			}
			arrow = t;
			arrow = " Å•";
			w += 4.0f + arrow.size().x;
			rect elm_rec({ w,h });
			elm_rec.centered({ 0,0 });
			for (auto& elm : elems) {
				elm_rec.at({ pos.x, pos.y + h * (id + 1) });
				button btn(elm_rec, elm);
				btn.set_function_normal([=](rect r, text t) {t = elm; r.centered({ 0,0 }).colored(pallet::white).draw(); t.centered({ -2,-2 }).draw(); });
				btn.set_function_hovered([=](rect r, text t) {t = elm; r.centered({ 0,0 }).colored(pallet::whitesmoke).draw(); t.centered({ -2,-2 }).draw(); });
				btn.set_function_pressed([=](rect r, text t) {t = elm; r.centered({ 0,0 }).colored(pallet::gray).draw(); t.centered({ -2,-2 }).draw(); });
				_element.push_back({ btn, id, elm });

				id++;
			}
			_menu_button = button(elm_rec, _element[_id]._text.get());
			_menu_button.set_function_normal([&](rect r, text t) {r.centered({ 0,0 }).colored(pallet::white).draw(); t.centered({ -2,-2 }).draw(); arrow.centered({ arrow.size().x + 2, -2 }).at(r.position() + point<double>{ r.size().x, 0}).draw(); });
			_menu_button.set_function_hovered([&](rect r, text t) {r.centered({ 0,0 }).colored(pallet::whitesmoke).draw(); t.centered({ -2,-2 }).draw(); arrow.centered({ arrow.size().x + 2, -2 }).at(r.position() + point<double>{ r.size().x, 0}).draw(); });
			_menu_button.set_function_pressed([&](rect r, text t) {r.centered({ 0,0 }).colored(pallet::gray).draw(); t.centered({ -2,-2 }).draw(); arrow.centered({ arrow.size().x + 2, -2 }).at(r.position() + point<double>{ r.size().x, 0}).draw();  });
		}

		bool pulldown::operator() (uint& id) {
			if (_menu_button()) {
				_isopen ^= 1;
			}
			if (_isopen) {
				for (auto&& e : _element) {
					if (e._button()) {
						id = e._id;
						return true;
					}
				}
			}
			else {
				for (auto&& e : _element) {
					if (e._id == id) {
						_id = id;
						return false;
					}
				}
			}
		}

		bool pulldown::operator() (text& txt) {
			if (_menu_button()) {
				_isopen ^= 1;
			}
			if (_isopen) {
				for (auto&& e : _element) {
					if (e._button()) {
						txt = e._text;
						return true;
					}
				}
			}
			else {
				for (auto&& e : _element) {
					if (e._text.get() == txt.get()) {
						_id = e._id;
						return false;
					}
				}
			}
		}
	}
}