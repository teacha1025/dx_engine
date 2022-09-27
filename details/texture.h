#pragma once
#include <vector>
#include <array>
#include "shape.h"
#include "def.h"
#include "color.h"
#include "pallet.h"
#include "draw_param.h"
#include "point.h"
#include "range.h"

namespace dx_engine {
	class texture : public detail::draw_object{
	private:
		point<double> _size{}, _position{}, _center{};

		int _handle = 0;
		std::vector<int> _div_handle;
		bool _isdiv = false;
		bool _isturn = false;
		bool _isflip = false;
		bool _istrans = true;
		double _angle = 0.0, _rate = 1.0;
		point<int> _div_num = { 1,1 };

		bool _failer = false;
		texture(const point<int>& size, const point<int>& pos, const point<int>& center, blend blend, byte param, int handle, bool turn, bool flip, double angle, double rate, filter mode);
	public:
		/// <summary>
		/// デフォルトコンストラクタ 64*64の白い矩形を作成
		/// </summary>
		texture();
		/// <summary>
		/// 大きさを指定して、テクスチャを作成
		/// </summary>
		/// <param name="size">テクスチャの大きさ</param>
		/// <param name="fill_color">テクスチャの色　デフォルトでは白</param>
		texture(const point<int>& size, const color& fill_color = pallet::white);
		/// <summary>
		/// ハンドルからテクスチャを作成
		/// </summary>
		/// <param name="handle">画像のハンドル</param>
		texture(int handle);
		/// <summary>
		/// パスからテクスチャを作成
		/// </summary>
		/// <param name="path">画像のパス</param>
		texture(const std::string& path);
		/// <summary>
		/// パスから画像分割のテクスチャを作成
		/// </summary>
		/// <param name="path">画像のパス</param>
		/// <param name="divnum">分割数</param>
		texture(const std::string& path, const point<int>& divnum);

		/// <summary>
		/// テクスチャの原点を設定
		/// </summary>
		/// <param name="center">原点とする座標</param>
		texture& centered(const dx_engine::point<double>& center);
		/// <summary>
		/// 原点を中心として回転させる
		/// </summary>
		/// <param name="angle">回転角度</param>
		texture& rotateed(double angle);
		/// <summary>
		/// ブレンドの設定する
		/// </summary>
		/// <param name="mode">ブレンドの種類</param>
		/// <param name="param">ブレンドの度合い[0-255]</param>
		texture& blend(dx_engine::blend mode, range<0, 255> param);
		/// <summary>
		/// フィルターの設定をする
		/// </summary>
		/// <param name="mode">フィルターの種類</param>
		texture& filter(dx_engine::filter mode);
		/// <summary>
		/// 原点を中心としてその座標に移動する
		/// </summary>
		/// <param name="position">座標</param>
		texture& at(const dx_engine::point<double>& position);
		/// <summary>
		/// 原点を中心に拡大する
		/// </summary>
		/// <param name="rate">倍率</param>
		/// <returns></returns>
		texture& extended(double rate);
		/// <summary>
		/// 左右反転させるかを設定する
		/// </summary>
		/// <param name="flag">trueなら左右反転する</param>
		texture& turned(bool flag);
		/// <summary>
		/// 上下反転させるかを設定する
		/// </summary>
		/// <param name="flag">trueなら上下反転する</param>
		texture& fliped(bool flag);
		/// <summary>
		/// テクスチャを透過するか設定する
		/// </summary>
		/// <param name="flag">trueなら透過する</param>
		texture& trans(bool flag);

		/// <summary>
		/// テクスチャの場所を返す
		/// </summary>
		/// <returns>テクスチャの座標</returns>
		point<double> position() const;
		/// <summary>
		/// テクスチャを描画する
		/// </summary>
		virtual void draw() override;

		/// <summary>
		/// 4点の座標を設定してアニメーションを再生する
		/// </summary>
		/// <param name="position">4点の座標の配列</param>
		void modofication_draw(const std::array<point<double>, 4>& position);

		/// <summary>
		/// 分割画像の要素にアクセスする
		/// </summary>
		/// <param name="i">要素数</param>
		/// <returns>分割画像のi番目のテクスチャ</returns>
		texture operator [](const uint& i)const;
	};
}