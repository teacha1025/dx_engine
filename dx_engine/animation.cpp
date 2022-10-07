#include <string>
#include <DxLib.h>
#include "../details/animation.h"
#include "../details/range.h"
#include "../details/logger.h"

namespace dx_engine {
	extern logger log;

	animation::animation(const std::string& path, const point<uint>& div) {
		_tex = texture(path, div);
	}
	animation::animation(const texture& tex) {
		_tex = tex;
	}

	void animation::add(uint id, const std::vector<uint>& order, uint interval, bool loop) {
		if (_data.contains(id)) {
			_data[id] = detail::animation_data{ ._interval = interval, ._loop = loop, ._order = order };
		}
		else {
			_data.insert(std::make_pair(id, detail::animation_data{ ._interval = interval, ._loop = loop, ._order = order }));
		}
	}

	void animation::set(uint id, bool reset_count) {
		_id = id;
		if (reset_count) {
			_count = 0;
		}
	}

	void animation::reset_interval(uint id, uint interval) {
		if (_data.contains(id)) {
			_data[id]._interval = interval;
		}
	}

	void animation::reset_order(uint id, const std::vector<uint>& order) {
		if (_data.contains(id)) {
			_data[id]._order = order;
		}
	}

	animation& animation::centered(const dx_engine::point<double>& center) {
		_tex.centered(center);
		return *this;
	}
	animation& animation::rotateed(double angle) {
		_tex.rotateed(angle);
		return *this;
	}
	animation& animation::blend(dx_engine::blend mode, range<0, 255> param) {
		_tex.blend(mode, param);
		return *this;
	}
	animation& animation::at(const dx_engine::point<double>& position) {
		_tex.at(position);
		return *this;
	}
	animation& animation::extended(double rate) {
		_tex.extended(rate);
		return *this;
	}
	animation& animation::turned(bool flag) {
		_tex.turned(flag);
		return *this;
	}
	animation& animation::fliped(bool flag) {
		_tex.fliped(flag);
		return *this;
	}

	void animation::update_index() {
		if (!_pause && !_end) {
			if (_count == _data.at(_id)._interval) {
				_count = 0;
				_index++;
				if (_data.at(_id)._loop) {
					_index %= _data.at(_id)._order.size();
				}
				else {
					if (_index == _data.at(_id)._order.size()) {
						_end = true;
					}
				}
			}
			_count++;
		}
	}

	void animation::modofication_play(const std::array<point<double>, 4>& position) {
		if (_data.contains(_id) && !_end) {
			update_index();
			_tex[_data.at(_id)._order.at(_index)].modofication_draw(position);
		}
	}

	void animation::play() {
		if (_data.contains(_id) && !_end) {
			update_index();
			_tex[_data.at(_id)._order.at(_index)].draw();

		}
	}
	void animation::pause() {
		_pause = true;
	}
	void animation::resume() {
		_pause = false;
	}
	void animation::reset() {
		_end = false, _pause = false;
	}

	bool animation::is_ended() const {
		return _end;
	}
}