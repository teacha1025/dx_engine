#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "texture.h"
#include "def.h"
#include "range.h"


namespace dx_engine {
	namespace detail {
		struct animation_data {
			uint _interval;
			bool _loop;
			std::vector<uint> _order;
		};
	}

	class animation {
	private:
		texture _tex;
		uint _id = UINT32_MAX;
		uint _index = 0;
		uint _count = 0;
		
		std::unordered_map<uint, detail::animation_data> _data;
		bool _end = false, _pause = false;

		void update_index();

	public:
		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		animation() = default;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="path"></param>
		/// <param name="div"></param>
		animation(const std::string& path, const point<uint>& div);
		animation(const texture& tex);

		void add(uint id, const std::vector<uint>& order, uint interval, bool loop = false);
		void set(uint id, bool reset_count = true);

		animation& centered(const dx_engine::point<double>& center);
		animation& rotateed(double angle);
		animation& blend(dx_engine::blend mode, range<0, 255> param);
		animation& at(const dx_engine::point<double>& position);
		animation& extended(double rate);
		animation& turned(bool flag);
		animation& fliped(bool flag);

		void modofication_play(const std::array<point<double>, 4>& position);

		void play();
		void pause();
		void resume();
		void reset();

		bool is_ended() const;
	};
}