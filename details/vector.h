#pragma once
#include <cmath>
#include "def.h"
#include "point.h"

namespace dx_engine {
	namespace vector {
		/// <summary>
		/// �傫���̓��
		/// </summary>
		/// <typeparam name="t">���l�^</typeparam>
		/// <param name="p">�x�N�g��</param>
		/// <returns>�x�N�g���̑傫���̓��</returns>
		template<typename t>
		double size_square(const point<t>& p) {
			return p.x * p.x + p.y * p.y;
		}

		/// <summary>
		/// �傫��
		/// </summary>
		/// <typeparam name="t">���l�^</typeparam>
		/// <param name="p">�x�N�g��</param>
		/// <returns>�x�N�g���̑傫��</returns>
		template<typename t>
		double size(const point<t>& p) {
			return std::sqrt(size_square(p));
		}

		/// <summary>
		/// �x�N�g������]������
		/// </summary>
		/// <typeparam name="t">���l�^</typeparam>
		/// <param name="p">�x�N�g��</param>
		/// <param name="angle">��]�̊p�x(rad)</param>
		/// <returns>angle������]�����x�N�g��</returns>
		template<typename t>
		point<t> rotate(const point<t>& p, const double& angle) {
			t x, y;
			x = (t)(p.x * std::cos(angle) - p.y * std::sin(angle));
			y = (t)(p.x * std::sin(angle) + p.y * std::cos(angle));
			return { x,y };
		}

		/// <summary>
		/// ��]���S���w�肵�č��W����]������
		/// </summary>
		/// <typeparam name="t">���l�^</typeparam>
		/// <param name="p">���W</param>
		/// <param name="c">��]���S</param>
		/// <param name="angle">��]�̊p�x(rad)</param>
		/// <returns>c�𒆐S��angle������]�������W</returns>
		template<typename t>
		point<t> rotate_at(const point<t>& p, const point<t>& c, const double& angle) {
			return rotate(p - c, angle) + c;
		}

		/// <summary>
		/// �x�N�g���̑傫����ύX
		/// </summary>
		/// <typeparam name="t">���l�^</typeparam>
		/// <param name="p">���̃x�N�g��</param>
		/// <param name="length">�ݒ肷�钷��</param>
		/// <returns>������length�ɂȂ����x�N�g��p</returns>
		template<typename t>
		point<t> set_length(const point<t>& p, const double& length) {
			if (size(p) == 0) {
				return { 0,0 };
			}
			auto v = p / size(p);
			return v * length;
		}

		/// <summary>
		/// �x�N�g���̊O��
		/// </summary>
		/// <typeparam name="t">���l�^</typeparam>
		/// <param name="v1">�x�N�g��1</param>
		/// <param name="v2">�x�N�g��2</param>
		/// <returns>v1 �~ v2</returns>
		template<typename t>
		t cross(const point<t>& v1, const point<t>& v2) {
			return v1.x * v2.y - v1.y * v2.x;
		}

		/// <summary>
		/// �x�N�g���̓���
		/// </summary>
		/// <typeparam name="t">���l�^</typeparam>
		/// <param name="v1">�x�N�g��1</param>
		/// <param name="v2">�x�N�g��2</param>
		/// <returns>v1�Ev2</returns>
		template<typename t>
		t dot(const point<t>& v1, const point<t>& v2) {
			return v1.x * v2.x + v1.y * v2.y;
		}

		/// <summary>
		/// �x�N�g���̊p�x
		/// </summary>
		/// <typeparam name="t">���l�^</typeparam>
		/// <param name="v">�x�N�g��</param>
		/// <returns>v�̊p�x</returns>
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
		/// �x�N�g�����m�̊p�x
		/// </summary>
		/// <typeparam name="t">���l�^</typeparam>
		/// <param name="v1">�x�N�g��1</param>
		/// <param name="v2">�x�N�g��2</param>
		/// <returns>v1����v2�ւ̊p�x</returns>
		template<typename t>
		double angle(const point<t>& v1, const point<t>& v2) {
			return angle(v2 - v1);
		}
	}
}