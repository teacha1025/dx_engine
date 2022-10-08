#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <Pdh.h>
#include <string>
#include <vector>
#include "def.h"
#include "draw_param.h"
#include "point.h"
#include "vector.h"
#include "color.h"
#include "pallet.h"
#include "device.h"
#include "range.h"

namespace dx_engine {

	enum class fullscreen_type {
		borderless_dotbydot,	//�{�[�_�[���X�E�B���h�E�@DOTbyDOT
		borderless_full,		//�{�[�_�[���X�E�B���h�E�@�ő�\��
		borderless_flexible,	//�{�[�_�[���X�E�B���h�E�@��ʑS�̂Ɉ������΂�
		fullscreen_dotbydot,	//�t���X�N���[���@DOTbyDOT
		fullscreen_full,		//�t���X�N���[���@�ő�\��
		fullscreen_flexible,	//�t���X�N���[���@��ʑS�̂Ɉ������΂�
	};
	namespace detail {

		class _system final {
		private:
			ULONGLONG delta_msec = 0;
			float _fps = 0, _max_fps = HUGE_VALF;
			bool _vsync = true;

			HANDLE _handle;
			DWORD _pid;

			SYSTEM_INFO _sysinfo;

			MEMORYSTATUSEX _memory_statu;

			PDH_HQUERY _hquery;
			PDH_HCOUNTER _hcounter;
			PDH_FMT_COUNTERVALUE _fmt{};

			double _cpu_usage = 0;
		public:
#ifdef _DEBUG
			/// <summary>
			/// �f�o�b�O���[�h���ǂ��� (�f�t�H���g��Debug���[�h�ł�true, Release���[�h�ł�false)
			/// </summary>
			bool debug_mode = true;
#else
			/// <summary>
			/// �f�o�b�O���[�h���ǂ��� (�f�t�H���g��Debug���[�h�ł�true, Release���[�h�ł�false)
			/// </summary>
			bool debug_mode = false;
#endif
			_system();

			/// <summary>
			/// �L�[�{�[�h
			/// </summary>
			device::keyboard keyboard;

			/// <summary>
			/// �}�E�X
			/// </summary>
			device::mouse mouse;

			/// <summary>
			/// �G���W���̃A�b�v�f�[�g�@���t���[���Ăяo��
			/// </summary>
			/// <returns>�t���[���𑱂��邩</returns>
			bool update();

			/// <summary>
			/// �O�t���[���Ƃ̍�
			/// </summary>
			/// <returns>�O�t���[�����牽�b�o������(float)</returns>
			float delta_sec() const;

			/// <summary>
			/// �O�t���[���Ƃ̍�
			/// </summary>
			/// <returns>�O�t���[�����牽�b�o������(double)</returns>
			double delta_sec_d() const;

			/// <summary>
			/// �t���[�����[�g�̌v�Z
			/// </summary>
			/// <returns>���݂̃t���[�����[�g</returns>
			float fps() const;

			/// <summary>
			/// ���������̐ݒ�
			/// </summary>
			/// <param name="flag">�����������g�p���邩</param>
			void vsync(bool flag);

			/// <summary>
			/// �t���[�����[�g�̍ő�l��ݒ�@���ݖ���
			/// </summary>
			/// <param name="value">�ő�l</param>
			void max_fps(float value);

			/// <summary>
			/// �v���Z�X�������̏����擾
			/// </summary>
			/// <returns>�v���Z�X�������̏��</returns>
			PROCESS_MEMORY_COUNTERS_EX process_memory_info() const;

			/// <summary>
			/// �������̏����擾
			/// </summary>
			/// <returns>�������̏��</returns>
			MEMORYSTATUSEX memory_info() const;

			/// <summary>
			/// CPU�g�p�ʂ̌v�Z
			/// </summary>
			/// <returns>CPU�g�p��</returns>
			double processor_usage() const;

			/// <summary>
			/// �V�X�e���̏����擾
			/// </summary>
			/// <returns>�V�X�e���̏��</returns>
			SYSTEM_INFO system_info() const;

			/// <summary>
			/// ���j�^�[�T�C�Y�̎擾
			/// </summary>
			/// <returns>���j�^�[�T�C�Y</returns>
			point<uint> monitor_size() const;

			~_system();
		};

		

		class _window final {
		private:
			point<uint> _size = { 1280, 960 };
			bool _fullscreen = false, _vsync = false;
			float _rate = 1.0f;
			std::string _title;
			color bg;
			fullscreen_type _screentype;

			int _mainscreen;
			point<int> _monitor_size, _letterbox_size;
		public:
			void background(const color& bg);
			void title(const std::string& title);

			void fullscreen(bool flag, fullscreen_type type = fullscreen_type::borderless_dotbydot);
			bool fullscreen() const;

			void size(const point<uint>& size);
			point<uint> size() const;

			void extends(float rate);
			float extends() const;

			bool update();

			void init();
			void init2();

			int back_screen() const;
		};

		
	}

	extern detail::_system systems;
	extern detail::_window window;
	
}