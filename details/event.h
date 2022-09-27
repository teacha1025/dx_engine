#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "def.h"
#include "range.h"


namespace dx_engine {
	/// <summary>
	/// イベントの継承元のクラス
	/// </summary>
	class event {
	public:
		/// <summary>
		/// イベントの更新
		/// </summary>
		/// <param name="count">経過時間</param>
		/// <returns>イベントを続けるか</returns>
		virtual bool update(uint count) = 0;
	};

	class event_manager {
	private:
		using func_type = std::function<bool(uint)>;
		using list_type = std::pair<func_type, uint>;
		std::vector<list_type> _event_list;

	public:
		/// <summary>
		/// イベントの追加
		/// </summary>
		/// <typeparam name="event_t">eventクラスが継承されたクラス</typeparam>
		/// <typeparam name="...Args">event_tのコンストラクタの引数</typeparam>
		/// <param name="...args">event_tのコンストラクタの引数</param>
		template<class event_t, class... Args>
		void add(Args&&... args) {
			_event_list.push_back(std::make_pair(std::bind(&event::update, std::make_shared<event_t>(args...), std::placeholders::_1), 0));
		}

		/// <summary>
		/// イベントの追加
		/// </summary>
		/// <param name="func">イベントが書かれた関数オブジェクト</param>
		void add(func_type func);

		/// <summary>
		/// イベントの更新
		/// </summary>
		void update();
	};
}