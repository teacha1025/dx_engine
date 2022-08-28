#pragma once
#include <string>
#include <memory>
#include <map>
#include <functional>
#include <cassert>
#include "pallet.h"
#include "details.h"
#include "exception.h"

#define SCENE_CONSTRUCTOR(cls) cls()=default;cls(const data_s& data){ constructor(data); init();}

namespace dx_engine {
	extern detail::_window window;
	struct empty_struct{};

	template<class data = empty_struct>
	class scene_manager;

	template<class data = empty_struct>
	class scene {
	private:
		using identifier = unsigned int;
		using data_type = data;
		using data_ptr = std::shared_ptr<data_type>;
		using manager_ptr = scene_manager<data_type>*;
	public:
		struct data_s {
			manager_ptr _scn_mng;
			std::shared_ptr<data_type> _data_ptr;
			identifier _id;

			data_s(manager_ptr sceneMng, const std::shared_ptr<data_type>& data_ptr, const identifier& id) {
				_scn_mng = sceneMng;
				_data_ptr = data_ptr;
				_id = id;
			}
		};
	private:
		manager_ptr _scn_mng = nullptr;
		data_ptr _datas = nullptr;
		identifier _id = UINT_MAX;
	protected:
		identifier id() const {
			return _id;
		}

		void change_scene(const identifier& _id, const unsigned int& fadeinout_count = 60, bool make_new_next_scene = false) const {
			_scn_mng->change(_id, fadeinout_count, make_new_next_scene);
		}

		data_ptr data() const {
			return _datas;
		}
	public:

		//SCENE_CONSTRUCTOR(scene)

		void constructor(const data_s& data) {
			_scn_mng = data._scn_mng;
			_datas = data._data_ptr;
			_id = data._id;
		}

		virtual void draw() {}
		virtual void update() {}
		virtual void init() {}
		virtual void load() {}

		virtual void draw_fadein(const double& rate) {
			draw();
			int alpha = static_cast<int>((1.0 - rate) * 255);
			rect(window.size()).centered({0,0}).at({0,0}).colored(pallet::black).blend(blend::alpha, alpha).draw();
		}

		virtual void draw_fadeout(const double& rate) {
			draw();
			int alpha = static_cast<int>(rate * 255);
			rect(window.size()).centered({ 0,0 }).at({ 0,0 }).colored(pallet::black).blend(blend::alpha, alpha).draw();
		}

		virtual void update_fadein(const double& rate) {
			update();
		}
		virtual void update_fadeout(const double& rate) {
			update();
		}
	};

	template<class data>
	class scene_manager final {
	private:
		using identifier = unsigned int;
		using scene_ptr = std::shared_ptr<scene<data>>;
		using data_ptr = std::shared_ptr<data>;
		using factor = std::function<scene_ptr()>;
		std::map<identifier, scene_ptr> _scenehash;
		std::map<identifier, factor> _factorhash;

		data_ptr _pdata;
		identifier _current_id = UINT_MAX;
		identifier _next_id = UINT_MAX;
		scene_ptr _p_current_scene;
		scene_ptr _p_next_scene;

		unsigned int _fade_counter = 0;
		unsigned int _fade_count = 60;

		enum scene_state {
			none,
			fadein,
			active,
			fadeout
		} _scene_state;

		void draw() {
			switch (_scene_state) {
			case none: {
				break;
			}
			case fadein: {
				_p_current_scene->draw_fadein(static_cast<double>(_fade_counter) / static_cast<double>(_fade_count));
				break;
			}
			case active: {
				_p_current_scene->draw();
				break;
			}
			case fadeout: {
				_p_current_scene->draw_fadeout(static_cast<double>(_fade_counter) / static_cast<double>(_fade_count));
				break;
			}
			default: {
				break;
			}
			}
		}

		void load() {
			_p_current_scene->load();
		}

	public:
		scene_manager() {
			_pdata = std::make_shared<data>();
			_scene_state = scene_state::active;
		}

		void set(const identifier& _id) {
			if (_id == UINT_MAX) {
				throw EXCEPT("Cannot register UINT_MAX as Scene ID.");
			}
			if (!_scenehash.contains(_id)) {
				throw EXCEPT(std::format("Scene ID :{} is not registered.", _id));
			}
			_current_id = _id;
			_p_current_scene = _scenehash[_id];
		}

		void change(const identifier& _id, const unsigned int& FadeInOutCount = 60, bool make_new_next_scene = false) {
			if (_id == UINT_MAX) {
				throw EXCEPT("Cannot register UINT_MAX as Scene ID.");
			}
			if (!_scenehash.contains(_id)) {
				throw EXCEPT(std::format("Scene ID :{} is not registered.", _id));
			}
			_next_id = _id;
			_p_next_scene = make_new_next_scene ? _factorhash[_id]() : _scenehash[_id];
			_fade_count = FadeInOutCount;
			_scene_state = fadeout;
		}

		template<class scenes_t>
		void add(const identifier& _id) {
			if (_id == UINT_MAX) {
				throw EXCEPT("Cannot register UINT_MAX as Scene ID.");
			}
			typename scenes_t::data_s scene_data_t(this, _pdata, _id);

			auto make_scene_ptr = [=]() {
				return std::make_shared<scenes_t>(scene_data_t);
			};

			auto it = _scenehash.find(_id);
			if (it != _scenehash.end()) {
				_scenehash[_id] = make_scene_ptr();
				_factorhash[_id] = make_scene_ptr;
			}
			else {
				_scenehash.emplace(_id, make_scene_ptr());
				_factorhash.emplace(_id, make_scene_ptr);
			}

			if (!_p_current_scene) {
				set(_id);
			}
		}


		void update() {
			if (!_p_current_scene) {
				throw EXCEPT("Scene Ptr is null.");
			}
			switch (_scene_state) {
			case none: {
				_fade_counter = 0;
				break;
			}
			case fadein: {
				_p_current_scene->update_fadein(static_cast<double>(_fade_counter) / static_cast<double>(_fade_count));

				_fade_counter++;
				if (_fade_counter >= _fade_count) {
					_scene_state = active;
				}
				break;
			}
			case active: {
				_p_current_scene->update();
				_fade_counter = 0;
				break;
			}
			case fadeout: {
				_p_current_scene->update_fadeout(static_cast<double>(_fade_counter) / static_cast<double>(_fade_count));
				_fade_counter++;
				if (_fade_counter >= _fade_count) {
					_fade_counter = 0;
					_scene_state = fadein;
					_p_current_scene = _p_next_scene;
					_current_id = _next_id;
					load();
				}
				break;
			}
			default: {
				break;
			}
			}

			draw();
		}

		identifier get_current_scene_id() const {
			return _current_id;
		}
	};
}