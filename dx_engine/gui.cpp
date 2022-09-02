#include <time.h>
#include "../details/gui.h"

namespace dx_engine {
	
	namespace gui {
		pulldown::pulldown(const std::vector<std::string>& elems, const point<int>& pos) {
			_position = pos;
			define padding = 6.0f;
			define font_size = 11u;
			if (elems.empty()) {
				_arrow.set_font("游ゴシック", font_size, 1u, font_type::anti_aliasing);
				_arrow = " ▼";
				rect elm_rec({ 24 + padding * 2.0f + _arrow.size().x,font_size + padding * 2.0f });
				elm_rec.centered({ 0,0 });
				elm_rec.at(pos);
				_arrow.centered({ _arrow.size().x + padding, -padding }).at(elm_rec.position() + point<double>{ elm_rec.size().x, 0});
				_menu_button = button(elm_rec, "", false);
			}
			else {
				text txt;
				txt.set_font("游ゴシック", font_size, 1u, font_type::anti_aliasing);
				uint id = 0;
				_box_w = 0, _box_h = font_size + padding * 2.0f;
				for (auto& elm : elems) {
					txt = elm;
					auto x = txt.size().x;
					_box_w = std::max(x, _box_w);
				}
				_arrow.set_font("游ゴシック", 8u, 1u, font_type::anti_aliasing);
				_arrow = " ▼";
				_box_w += padding * 2.0f + _arrow.size().x;
				rect elm_rec({ _box_w,_box_h });
				elm_rec.centered({ 0,0 });
				for (auto& elm : elems) {
					elm_rec.at({ pos.x, pos.y + _box_h * (id + 1) });
					button btn(elm_rec, elm);
					btn.set_font("游ゴシック", font_size, 1u, font_type::anti_aliasing);
					btn.set_function_normal([=](rect r, text t) {t = elm; r.centered({ 0,0 }).colored(pallet::white).draw(); t.centered({ -padding,-padding }).draw(); });
					btn.set_function_hovered([=](rect r, text t) {t = elm; r.centered({ 0,0 }).colored(pallet::lightskyblue).draw(); t.centered({ -padding,-padding }).draw(); });
					btn.set_function_pressed([=](rect r, text t) {t = elm; r.centered({ 0,0 }).colored(pallet::skyblue).draw(); t.centered({ -padding,-padding }).draw(); });
					_element.push_back({ btn, id, elm });

					id++;
				}
				elm_rec.at(pos);
				_arrow.centered({ _arrow.size().x + padding, _arrow.size().y / 2.0}).at(elm_rec.position() + point<double>{ _box_w, _box_h / 2.0f});
				_menu_button = button(elm_rec, _element[_id]._text.get());
				_menu_button.set_text(_element[_id]._text.get());
				_menu_button.set_font("游ゴシック", font_size, 1u, font_type::anti_aliasing);
				_menu_button.set_function_normal([=](rect r, text t) {r.centered({ 0,0 }).colored(pallet::white).draw(); t.centered({ -padding,-padding }).draw();  });
				_menu_button.set_function_hovered([=](rect r, text t) {r.centered({ 0,0 }).colored(pallet::whitesmoke).draw(); t.centered({ -padding,-padding }).draw(); });
				_menu_button.set_function_pressed([=](rect r, text t) {r.centered({ 0,0 }).colored(pallet::gray).draw(); t.centered({ -padding,-padding }).draw(); });
			}
		}

		pulldown::~pulldown() {
			_element.clear();
			_element.shrink_to_fit();
		}

		bool pulldown::operator() (uint& id) {
			if (_menu_button()) {
				_isopen ^= 1;
			}
			_arrow.draw();
			rect({ _box_w, _box_h }).colored(_isopen ? pallet::orange : pallet::black).centered({ 0,0 }).fill(false).at(_position).draw();
			if (_element.empty()) return false;
			if (_isopen) {

				rect({ _box_w, _box_h * _element.size() }).colored(pallet::black).blend(blend::alpha, 128).centered({-2,-2}).at(_position + point<int>{0, _box_h}).draw();
				

				for (auto&& e : _element) {
					if (e._button()) {
						id = e._id;
						_id = e._id;
						_menu_button.set_text(_element[_id]._text.get());
						_isopen = false;
						return true;
					}
				}
				rect({ _box_w, _box_h * _element.size() }).colored(pallet::black).centered({ 0,0 }).fill(false).at(_position + point<int>{0, _box_h}).draw();
			}
			_id = id;
			_menu_button.set_text(_element[_id]._text.get());
			return false;
		}

		bool pulldown::operator() (text& txt) {
			if (_menu_button()) {
				_isopen ^= 1;
			}
			_arrow.draw();
			if (_element.empty()) return false;
			if (_isopen) {
				for (auto&& e : _element) {
					if (e._button()) {
						txt = e._text;
						_id = e._id;
						_menu_button.set_text(_element[_id]._text.get());
						_isopen = false;
						return true;
					}
				}
			}
			else {
				for (auto&& e : _element) {
					if (e._text.get() == txt.get()) {
						_id = e._id;
						_menu_button.set_text(_element[_id]._text.get());
						return false;
					}
				}
			}
			return false;
		}
	}
}