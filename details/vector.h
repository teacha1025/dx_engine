#pragma once
#include <cmath>
#include "def.h"
#include "point.h"

namespace dx_engine {
	namespace vector {
		/// <summary>
		/// 大きさの二乗
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="p">ベクトル</param>
		/// <returns>ベクトルの大きさの二乗</returns>
		template<typename t>
		double size_square(const point<t>& p) {
			return p.x * p.x + p.y * p.y;
		}

		/// <summary>
		/// 大きさ
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="p">ベクトル</param>
		/// <returns>ベクトルの大きさ</returns>
		template<typename t>
		double size(const point<t>& p) {
			return std::sqrt(size_square(p));
		}

		/// <summary>
		/// ベクトルを回転させる
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="p">ベクトル</param>
		/// <param name="angle">回転の角度(rad)</param>
		/// <returns>angleだけ回転したベクトル</returns>
		template<typename t>
		point<t> rotate(const point<t>& p, const double& angle) {
			t x, y;
			x = (t)(p.x * std::cos(angle) - p.y * std::sin(angle));
			y = (t)(p.x * std::sin(angle) + p.y * std::cos(angle));
			return { x,y };
		}

		/// <summary>
		/// 回転中心を指定して座標を回転させる
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="p">座標</param>
		/// <param name="c">回転中心</param>
		/// <param name="angle">回転の角度(rad)</param>
		/// <returns>cを中心にangleだけ回転した座標</returns>
		template<typename t>
		point<t> rotate_at(const point<t>& p, const point<t>& c, const double& angle) {
			return rotate(p - c, angle) + c;
		}

		/// <summary>
		/// ベクトルの大きさを変更
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="p">元のベクトル</param>
		/// <param name="length">設定する長さ</param>
		/// <returns>長さがlengthになったベクトルp</returns>
		template<typename t>
		point<t> set_length(const point<t>& p, const double& length) {
			if (size(p) == 0) {
				return { 0,0 };
			}
			auto v = p / size(p);
			return v * length;
		}

		/// <summary>
		/// ベクトルの外積
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="v1">ベクトル1</param>
		/// <param name="v2">ベクトル2</param>
		/// <returns>v1 × v2</returns>
		template<typename t>
		t cross(const point<t>& v1, const point<t>& v2) {
			return v1.x * v2.y - v1.y * v2.x;
		}

		/// <summary>
		/// ベクトルの内積
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="v1">ベクトル1</param>
		/// <param name="v2">ベクトル2</param>
		/// <returns>v1・v2</returns>
		template<typename t>
		t dot(const point<t>& v1, const point<t>& v2) {
			return v1.x * v2.x + v1.y * v2.y;
		}

		/// <summary>
		/// ベクトルの角度
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="v">ベクトル</param>
		/// <returns>vの角度</returns>
		template<typename t>
		double angle(const point<t>& v) {
			if (v.x == 0) {
				return v.y >= 0 ? PI_HALF : -PI_HALF;
			}
			if (v.y == 0) {
				return v.x >= 0 ? 0 : PI;
			}
			return atan(v.y / v.x);
		}

		/// <summary>
		/// ベクトル同士の角度
		/// </summary>
		/// <typeparam name="t">数値型</typeparam>
		/// <param name="v1">ベクトル1</param>
		/// <param name="v2">ベクトル2</param>
		/// <returns>v1からv2への角度</returns>
		template<typename t>
		double angle(const point<t>& v1, const point<t>& v2) {
			return angle(v2 - v1);
		}
	}
}