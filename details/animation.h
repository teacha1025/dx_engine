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
		/// パスからアニメーションを作成する
		/// </summary>
		/// <param name="path">画像のパス</param>
		/// <param name="div">分割数</param>
		animation(const std::string& path, const point<uint>& div);

		/// <summary>
		/// テクスチャからアニメーションを作成する
		/// </summary>
		/// <param name="tex">アニメーションにするテクスチャ</param>
		animation(const texture& tex);

		/// <summary>
		/// アニメーションの定義を追加する
		/// </summary>
		/// <param name="id">アニメーションのID</param>
		/// <param name="order">アニメーションする画像の番号(左上から右に向かって0,1,2,....)</param>
		/// <param name="interval">画像切り替えのフレーム数</param>
		/// <param name="loop">ループするかどうか</param>
		void add(uint id, const std::vector<uint>& order, uint interval, bool loop = false);
		/// <summary>
		/// アニメーションのIDをセットする
		/// </summary>
		/// <param name="id">アニメーションID</param>
		/// <param name="reset_count">画像を一番初めに戻すか</param>
		void set(uint id, bool reset_count = true);

		/// <summary>
		/// 原点とする座標を設定する
		/// </summary>
		/// <param name="center">原点とする座標</param>
		animation& centered(const dx_engine::point<double>& center);
		/// <summary>
		/// 原点を中心として回転させる
		/// </summary>
		/// <param name="angle">回転角度</param>
		animation& rotateed(double angle);
		/// <summary>
		/// ブレンドの設定する
		/// </summary>
		/// <param name="mode">ブレンドの種類</param>
		/// <param name="param">ブレンドの度合い[0-255]</param>
		animation& blend(dx_engine::blend mode, range<0, 255> param);
		/// <summary>
		/// 原点を中心としてその座標に移動する
		/// </summary>
		/// <param name="position">座標</param>
		animation& at(const dx_engine::point<double>& position);
		/// <summary>
		/// 原点を中心に拡大する
		/// </summary>
		/// <param name="rate"></param>
		/// <returns></returns>
		animation& extended(double rate);
		/// <summary>
		/// 左右反転させるかを設定する
		/// </summary>
		/// <param name="flag">trueなら左右反転する</param>
		animation& turned(bool flag);
		/// <summary>
		/// 上下反転させるかを設定する
		/// </summary>
		/// <param name="flag">trueなら上下反転する</param>
		animation& fliped(bool flag);

		/// <summary>
		/// 4点の座標を設定してアニメーションを再生する
		/// </summary>
		/// <param name="position">4点の座標の配列</param>
		void modofication_play(const std::array<point<double>, 4>& position);

		/// <summary>
		///　アニメーションを再生する
		/// </summary>
		void play();
		/// <summary>
		/// アニメーションを一時停止する
		/// </summary>
		void pause();
		/// <summary>
		/// アニメーションを再開する
		/// </summary>
		void resume();
		/// <summary>
		/// アニメーションを最初から再生する
		/// </summary>
		void reset();

		/// <summary>
		/// アニメーションの終わりを検出する
		/// </summary>
		/// <returns>アニメーションの再生が終わったかどうか</returns>
		bool is_ended() const;
	};
}