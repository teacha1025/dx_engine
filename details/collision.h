#pragma once
#include "shape.h"
#include "vector.h"

namespace dx_engine {
	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <typeparam name="t">数値型</typeparam>
	/// <param name="a">座標</param>
	/// <param name="b">座標</param>
	/// <returns>当たったかどうか</returns>
	template<Number t>
	bool collision(point<t> a, point<t> b) {
		return a == b;
	}

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <typeparam name="t">数値型</typeparam>
	/// <param name="p">座標</param>
	/// <param name="l">線分</param>
	/// <returns>当たったかどうか</returns>
	template<Number t>
	bool collision(point<t> p, line l) {
		auto lp = l.position();
		if (lp.empty()) {
			return false;
		}
		if (lp.size() == 1u) {
			return p == lp.at(0);
		}
		for (size_t i = 0u; i < lp.size() - 1u; i++) {
			point<double> ab = lp.at(i + 1u) - lp.at(i), ap = p - lp.at(i);
			double s_ab = vector::size(ab), s_ap = vector::size(ap);
			if (vector::dot(ab, ap) == s_ab * s_ap) {
				if (s_ab >= s_ap) {
					return true;
				}
			}
		}

		return false;
	}

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <typeparam name="t">数値型</typeparam>
	/// <param name="l">線分</param>
	/// <param name="p">座標</param>
	/// <returns>当たったかどうか</returns>
	template<Number t>
	bool collision(line l, point<t> p) {
		return collision(p, l);
	}

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <typeparam name="t">数値型</typeparam>
	/// <param name="c">円</param>
	/// <param name="p">座標</param>
	/// <returns>当たったかどうか</returns>
	template<Number t>
	bool collision(circle c, point<t> p) {
		return vector::size_square(c.position() - c.center() - p) < c.size() * c.size();
	}

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <typeparam name="t">数値型</typeparam>
	/// <param name="p">座標</param>
	/// <param name="p">円</param>
	/// <returns>当たったかどうか</returns>
	template<Number t>
	bool collision(point<t> p, circle c) {
		return collision(c, p);
	}

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="l1">線分</param>
	/// <param name="l2">線分</param>
	/// <returns>当たったかどうか</returns>
	bool collision(line l1, line l2);

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="c">円</param>
	/// <param name="l">線分</param>
	/// <returns>当たったかどうか</returns>
	bool collision(circle c, line l);

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="l">線分</param>
	/// <param name="c">円</param>
	/// <returns>当たったかどうか</returns>
	bool collision(line l, circle c);

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="c1">円</param>
	/// <param name="c2">円</param>
	/// <returns>当たったかどうか</returns>
	bool collision(circle c1, circle c2);

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <typeparam name="t">数値型</typeparam>
	/// <param name="p">座標</param>
	/// <param name="r">矩形</param>
	/// <returns>当たったかどうか</returns>
	template<Number t>
	bool collision(point<t> p, rect r) {
		auto [a, b, c, d] = r.verteces();
		point<double> _p = { SCAST(double, p.x), SCAST(double, p.y) };
		if (
			vector::cross(b - a, _p - a) > 0 &&
			vector::cross(c - b, _p - b) > 0 &&
			vector::cross(d - c, _p - c) > 0 &&
			vector::cross(a - d, _p - d) > 0
			) {
			return true;
		}
		return false;
	}

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <typeparam name="t">数値型</typeparam>
	/// <param name="r">矩形</param>
	/// <param name="p">座標</param>
	/// <returns>当たったかどうか</returns>
	template<Number t>
	bool collision(rect r, point<t> p) {
		return collision(p, r);
	}

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="c">円</param>
	/// <param name="r">矩形</param>
	/// <returns>当たったかどうか</returns>
	bool collision(circle c, rect r);

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="r">矩形</param>
	/// <param name="c">円</param>
	/// <returns>当たったかどうか</returns>
	bool collision(rect r, circle c);

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="r">矩形</param>
	/// <param name="l">線分</param>
	/// <returns>当たったかどうか</returns>
	bool collision(rect r, line l);

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="l">線分</param>
	/// <param name="r">矩形</param>
	/// <returns>当たったかどうか</returns>
	bool collision(line l, rect r);

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="r1">矩形</param>
	/// <param name="r2">矩形</param>
	/// <returns>当たったかどうか</returns>
	bool collision(rect r1, rect r2);
}