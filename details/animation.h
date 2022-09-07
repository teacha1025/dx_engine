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
		/// �f�t�H���g�R���X�g���N�^
		/// </summary>
		animation() = default;
		/// <summary>
		/// �p�X����A�j���[�V�������쐬����
		/// </summary>
		/// <param name="path">�摜�̃p�X</param>
		/// <param name="div">������</param>
		animation(const std::string& path, const point<uint>& div);

		/// <summary>
		/// �e�N�X�`������A�j���[�V�������쐬����
		/// </summary>
		/// <param name="tex">�A�j���[�V�����ɂ���e�N�X�`��</param>
		animation(const texture& tex);

		/// <summary>
		/// �A�j���[�V�����̒�`��ǉ�����
		/// </summary>
		/// <param name="id">�A�j���[�V������ID</param>
		/// <param name="order">�A�j���[�V��������摜�̔ԍ�(���ォ��E�Ɍ�������0,1,2,....)</param>
		/// <param name="interval">�摜�؂�ւ��̃t���[����</param>
		/// <param name="loop">���[�v���邩�ǂ���</param>
		void add(uint id, const std::vector<uint>& order, uint interval, bool loop = false);
		/// <summary>
		/// �A�j���[�V������ID���Z�b�g����
		/// </summary>
		/// <param name="id">�A�j���[�V����ID</param>
		/// <param name="reset_count">�摜����ԏ��߂ɖ߂���</param>
		void set(uint id, bool reset_count = true);

		/// <summary>
		/// ���_�Ƃ�����W��ݒ肷��
		/// </summary>
		/// <param name="center">���_�Ƃ�����W</param>
		animation& centered(const dx_engine::point<double>& center);
		/// <summary>
		/// ���_�𒆐S�Ƃ��ĉ�]������
		/// </summary>
		/// <param name="angle">��]�p�x</param>
		animation& rotateed(double angle);
		/// <summary>
		/// �u�����h�̐ݒ肷��
		/// </summary>
		/// <param name="mode">�u�����h�̎��</param>
		/// <param name="param">�u�����h�̓x����[0-255]</param>
		animation& blend(dx_engine::blend mode, range<0, 255> param);
		/// <summary>
		/// ���_�𒆐S�Ƃ��Ă��̍��W�Ɉړ�����
		/// </summary>
		/// <param name="position">���W</param>
		animation& at(const dx_engine::point<double>& position);
		/// <summary>
		/// ���_�𒆐S�Ɋg�傷��
		/// </summary>
		/// <param name="rate"></param>
		/// <returns></returns>
		animation& extended(double rate);
		/// <summary>
		/// ���E���]�����邩��ݒ肷��
		/// </summary>
		/// <param name="flag">true�Ȃ獶�E���]����</param>
		animation& turned(bool flag);
		/// <summary>
		/// �㉺���]�����邩��ݒ肷��
		/// </summary>
		/// <param name="flag">true�Ȃ�㉺���]����</param>
		animation& fliped(bool flag);

		/// <summary>
		/// 4�_�̍��W��ݒ肵�ăA�j���[�V�������Đ�����
		/// </summary>
		/// <param name="position">4�_�̍��W�̔z��</param>
		void modofication_play(const std::array<point<double>, 4>& position);

		/// <summary>
		///�@�A�j���[�V�������Đ�����
		/// </summary>
		void play();
		/// <summary>
		/// �A�j���[�V�������ꎞ��~����
		/// </summary>
		void pause();
		/// <summary>
		/// �A�j���[�V�������ĊJ����
		/// </summary>
		void resume();
		/// <summary>
		/// �A�j���[�V�������ŏ�����Đ�����
		/// </summary>
		void reset();

		/// <summary>
		/// �A�j���[�V�����̏I�������o����
		/// </summary>
		/// <returns>�A�j���[�V�����̍Đ����I��������ǂ���</returns>
		bool is_ended() const;
	};
}