#pragma once
#include "range.h"
#include <DxLib.h>

namespace dx_engine {
	struct hsv;

	/// <summary>
	/// RGB�J���[�������N���X
	/// </summary>
	struct color {
		/// <summary>
		/// RGBA�̗v�f[0-255]
		/// </summary>
		byte r, g, b, a;

		/// <summary>
		/// �f�t�H���g�R���X�g���N�^�@�f�t�H���g�ł͍��F
		/// </summary>
		constexpr color() :r(0), g(0), b(0), a(255) {}

		/// <summary>
		/// RGBA���w�肵�ĐF���쐬
		/// </summary>
		/// <param name="_r">��[0-255]</param>
		/// <param name="_g">��[0-255]</param>
		/// <param name="_b">��[0-255]</param>
		/// <param name="_a">���l[0-255]</param>
		constexpr color(byte _r, byte _g, byte _b, byte _a = 255) : r(_r), g(_g), b(_b), a(_a) {}

		/// <summary>
		/// �ق��̐F����쐬
		/// </summary>
		/// <param name="color">�ق��̐F</param>
		/// <param name="_a">���l[0-255]</param>
		constexpr color(const color& color, byte _a) : r(color.r), g(color.g), b(color.b), a(_a) {}

		/// <summary>
		/// HSV�J���[�ւ̕ϊ�
		/// </summary>
		operator hsv() const;

		/// <summary>
		/// �F��ϊ�
		/// </summary>
		/// <returns>���l�����ꂽ�F</returns>
		unsigned int to_int() const;
	};

	struct hsv {
		/// <summary>
		/// �F��[0-360]
		/// </summary>
		int h;

		/// <summary>
		/// �ʓx[0.0-1.0]
		/// </summary>
		double s;

		/// <summary>
		/// ���x[0.0-1.0]
		/// </summary>
		double v;

		/// <summary>
		/// ���l[0-255]
		/// </summary>
		byte a;

		/// <summary>
		/// �f�t�H���g�R���X�g���N�^�@�f�t�H���g�ł͍�
		/// </summary>
		constexpr hsv() :h(0), s(0), v(0), a(255) {};

		/// <summary>
		/// HSVA���w�肵�ĐF���쐬
		/// </summary>
		/// <param name="h">�F��[0-360]</param>
		/// <param name="s">�ʓx[0.0-1.0]</param>
		/// <param name="v">���x[0.0-1.0]</param>
		/// <param name="a">���l[0-255]</param>
		constexpr hsv(range<0, 360> h, range<0.0, 1.0> s, range<0.0, 1.0> v, byte a = 255) :h(h.get()), s(s.get()), v(v.get()), a(a) {}

		/// <summary>
		/// �ق��̐F����쐬
		/// </summary>
		/// <param name="color">�ق��̐F</param>
		/// <param name="a">���l[0-255]���l[0-255]</param>
		constexpr hsv(const hsv& color, byte a) : h(color.h), s(color.s), v(color.v), a(a) {}

		/// <summary>
		/// RGB�J���[�ւ̕ϊ�
		/// </summary>
		operator color() const;

		/// <summary>
		/// �F��ϊ�
		/// </summary>
		/// <returns>���l�����ꂽ�F</returns>
		unsigned int to_int() const;
	};
}