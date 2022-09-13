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
		/// �f�t�H���g�R���X�g���N�^ 64*64�̔�����`���쐬
		/// </summary>
		texture();
		/// <summary>
		/// �傫�����w�肵�āA�e�N�X�`�����쐬
		/// </summary>
		/// <param name="size">�e�N�X�`���̑傫��</param>
		/// <param name="fill_color">�e�N�X�`���̐F�@�f�t�H���g�ł͔�</param>
		texture(const point<int>& size, const color& fill_color = pallet::white);
		/// <summary>
		/// �n���h������e�N�X�`�����쐬
		/// </summary>
		/// <param name="handle">�摜�̃n���h��</param>
		texture(int handle);
		/// <summary>
		/// �p�X����e�N�X�`�����쐬
		/// </summary>
		/// <param name="path">�摜�̃p�X</param>
		texture(const std::string& path);
		/// <summary>
		/// �p�X����摜�����̃e�N�X�`�����쐬
		/// </summary>
		/// <param name="path">�摜�̃p�X</param>
		/// <param name="divnum">������</param>
		texture(const std::string& path, const point<int>& divnum);

		/// <summary>
		/// �e�N�X�`���̌��_��ݒ�
		/// </summary>
		/// <param name="center">���_�Ƃ�����W</param>
		texture& centered(const dx_engine::point<double>& center);
		/// <summary>
		/// ���_�𒆐S�Ƃ��ĉ�]������
		/// </summary>
		/// <param name="angle">��]�p�x</param>
		texture& rotateed(double angle);
		/// <summary>
		/// �u�����h�̐ݒ肷��
		/// </summary>
		/// <param name="mode">�u�����h�̎��</param>
		/// <param name="param">�u�����h�̓x����[0-255]</param>
		texture& blend(dx_engine::blend mode, range<0, 255> param);
		/// <summary>
		/// �t�B���^�[�̐ݒ������
		/// </summary>
		/// <param name="mode">�t�B���^�[�̎��</param>
		texture& filter(dx_engine::filter mode);
		/// <summary>
		/// ���_�𒆐S�Ƃ��Ă��̍��W�Ɉړ�����
		/// </summary>
		/// <param name="position">���W</param>
		texture& at(const dx_engine::point<double>& position);
		/// <summary>
		/// ���_�𒆐S�Ɋg�傷��
		/// </summary>
		/// <param name="rate">�{��</param>
		/// <returns></returns>
		texture& extended(double rate);
		/// <summary>
		/// ���E���]�����邩��ݒ肷��
		/// </summary>
		/// <param name="flag">true�Ȃ獶�E���]����</param>
		texture& turned(bool flag);
		/// <summary>
		/// �㉺���]�����邩��ݒ肷��
		/// </summary>
		/// <param name="flag">true�Ȃ�㉺���]����</param>
		texture& fliped(bool flag);
		/// <summary>
		/// �e�N�X�`���𓧉߂��邩�ݒ肷��
		/// </summary>
		/// <param name="flag">true�Ȃ瓧�߂���</param>
		texture& trans(bool flag);

		/// <summary>
		/// �e�N�X�`���̏ꏊ��Ԃ�
		/// </summary>
		/// <returns>�e�N�X�`���̍��W</returns>
		point<double> position() const;
		/// <summary>
		/// �e�N�X�`����`�悷��
		/// </summary>
		virtual void draw() override;

		/// <summary>
		/// 4�_�̍��W��ݒ肵�ăA�j���[�V�������Đ�����
		/// </summary>
		/// <param name="position">4�_�̍��W�̔z��</param>
		void modofication_draw(const std::array<point<double>, 4>& position);

		/// <summary>
		/// �����摜�̗v�f�ɃA�N�Z�X����
		/// </summary>
		/// <param name="i">�v�f��</param>
		/// <returns>�����摜��i�Ԗڂ̃e�N�X�`��</returns>
		texture operator [](const uint& i)const;
	};
}