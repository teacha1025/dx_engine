#pragma once
#include "def.h"
#include "range.h"
#include "point.h"

namespace dx_engine {
	namespace ease {
		namespace in {
			double sine(const range<0.0, 1.0>& t);
			double quad(const range<0.0, 1.0>& t);
			double cubic(const range<0.0, 1.0>& t);
			double quart(const range<0.0, 1.0>& t);
			double quint(const range<0.0, 1.0>& t);
			double expo(const range<0.0, 1.0>& t);
			double circ(const range<0.0, 1.0>& t);
			double back(const range<0.0, 1.0>& t);
			double elastic(const range<0.0, 1.0>& t);
			double bounce(const range<0.0, 1.0>& t);
		}
		namespace out {
			double sine(const range<0.0, 1.0>& t);
			double quad(const range<0.0, 1.0>& t);
			double cubic(const range<0.0, 1.0>& t);
			double quart(const range<0.0, 1.0>& t);
			double quint(const range<0.0, 1.0>& t);
			double expo(const range<0.0, 1.0>& t);
			double circ(const range<0.0, 1.0>& t);
			double back(const range<0.0, 1.0>& t);
			double elastic(const range<0.0, 1.0>& t);
			double bounce(const range<0.0, 1.0>& t);
		}
		namespace inout {
			double sine(const range<0.0, 1.0>& t);
			double quad(const range<0.0, 1.0>& t);
			double cubic(const range<0.0, 1.0>& t);
			double quart(const range<0.0, 1.0>& t);
			double quint(const range<0.0, 1.0>& t);
			double expo(const range<0.0, 1.0>& t);
			double circ(const range<0.0, 1.0>& t);
			double back(const range<0.0, 1.0>& t);
			double elastic(const range<0.0, 1.0>& t);
			double bounce(const range<0.0, 1.0>& t);
		}
	}

	namespace lerp {
		/// <summary>
		/// �x�W�F���
		/// </summary>
		/// <param name="cp">����_�̔z��</param>
		/// <param name="t">����[0.0-1.0]</param>
		/// <returns>t�ɂ�������W</returns>
		point<double> bezier(std::vector<point<double>> cp, const range<0.0, 1.0>& t);
		/// <summary>
		/// B-�X�v���C�����
		/// </summary>
		/// <param name="cp">����X�̔z��</param>
		/// <param name="t">����</param>
		/// <param name="degree">�x��</param>
		/// <returns>t�ɂ�������W</returns>
		point<double> b_spline(std::vector<point<double>> cp, double t, int degree);
	}
}