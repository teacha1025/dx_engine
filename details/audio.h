#pragma once
#include <string>
#include "def.h"
#include "range.h"


namespace dx_engine {
	class audio {
	private:
		int _handle = 0;
		float _pan = 0.0f, _volume = 1.0f;
		bool _loop;
		bool _playing = false, _start_at_head = true;
	public:
		/// <summary>
		/// �f�t�H���g�R���X�g���N�^
		/// </summary>
		audio() = default;
		/// <summary>
		/// �p�X���特�����쐬
		/// </summary>
		/// <param name="path">�����̃p�X</param>
		/// <param name="loop">���������[�v�����邩</param>
		audio(const std::string& path, bool loop);

		/// <summary>
		/// �p���̐ݒ�
		/// </summary>
		/// <param name="panpal">�����̈ʒu[-1.0f, 1.0f] +���͉E�A�|���͍�</param>
		audio& pan(range<-1.0f, 1.0f> panpal);
		/// <summary>
		/// ���ʂ̐ݒ�
		/// </summary>
		/// <param name="value">����[0.0f-1.0f]</param>
		audio& volume(range<0.0f, 1.0f> value);

		/// <summary>
		/// �����̍Đ����J�n
		/// </summary>
		void play();
		/// <summary>
		/// �������ꎞ��~����
		/// </summary>
		void pause();
		/// <summary>
		/// �������~����
		/// </summary>
		void stop();

		/// <summary>
		/// �������Đ������ǂ����m�F����
		/// </summary>
		/// <returns>true�Ȃ特�����Đ�����Ă���</returns>
		bool is_playing() const;
	};
}