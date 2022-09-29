#pragma once
#include "range.h"
#include <DxLib.h>

namespace dx_engine {
	struct hsv;

	/// <summary>
	/// RGBカラーを扱うクラス
	/// </summary>
	struct color {
		/// <summary>
		/// RGBAの要素[0-255]
		/// </summary>
		byte r, g, b, a;

		/// <summary>
		/// デフォルトコンストラクタ　デフォルトでは黒色
		/// </summary>
		constexpr color() :r(0), g(0), b(0), a(255) {}

		/// <summary>
		/// RGBAを指定して色を作成
		/// </summary>
		/// <param name="_r">赤[0-255]</param>
		/// <param name="_g">緑[0-255]</param>
		/// <param name="_b">青[0-255]</param>
		/// <param name="_a">α値[0-255]</param>
		constexpr color(byte _r, byte _g, byte _b, byte _a = 255) : r(_r), g(_g), b(_b), a(_a) {}

		/// <summary>
		/// ほかの色から作成
		/// </summary>
		/// <param name="color">ほかの色</param>
		/// <param name="_a">α値[0-255]</param>
		constexpr color(const color& color, byte _a) : r(color.r), g(color.g), b(color.b), a(_a) {}

		/// <summary>
		/// HSVカラーへの変換
		/// </summary>
		operator hsv() const;

		/// <summary>
		/// 色を変換
		/// </summary>
		/// <returns>数値化された色</returns>
		unsigned int to_int() const;
	};

	struct hsv {
		/// <summary>
		/// 色相[0-360]
		/// </summary>
		int h;

		/// <summary>
		/// 彩度[0.0-1.0]
		/// </summary>
		double s;

		/// <summary>
		/// 明度[0.0-1.0]
		/// </summary>
		double v;

		/// <summary>
		/// α値[0-255]
		/// </summary>
		byte a;

		/// <summary>
		/// デフォルトコンストラクタ　デフォルトでは黒
		/// </summary>
		constexpr hsv() :h(0), s(0), v(0), a(255) {};

		/// <summary>
		/// HSVAを指定して色を作成
		/// </summary>
		/// <param name="h">色相[0-360]</param>
		/// <param name="s">彩度[0.0-1.0]</param>
		/// <param name="v">明度[0.0-1.0]</param>
		/// <param name="a">α値[0-255]</param>
		constexpr hsv(range<0, 360> h, range<0.0, 1.0> s, range<0.0, 1.0> v, byte a = 255) :h(h.get()), s(s.get()), v(v.get()), a(a) {}

		/// <summary>
		/// ほかの色から作成
		/// </summary>
		/// <param name="color">ほかの色</param>
		/// <param name="a">α値[0-255]α値[0-255]</param>
		constexpr hsv(const hsv& color, byte a) : h(color.h), s(color.s), v(color.v), a(a) {}

		/// <summary>
		/// RGBカラーへの変換
		/// </summary>
		operator color() const;

		/// <summary>
		/// 色を変換
		/// </summary>
		/// <returns>数値化された色</returns>
		unsigned int to_int() const;
	};
}