#pragma once
#include "key.h"
#include "mouse.h"
#include "point.h"

namespace dx_engine {
	namespace detail {
		namespace device {
			struct keyboard {
				keyboard();

				/// <summary>
				/// 1�L�[
				///</summary>
				_key Key1;

				/// <summary>
				/// 2�L�[
				///</summary>
				_key Key2;

				/// <summary>
				/// 3�L�[
				///</summary>
				_key Key3;

				/// <summary>
				/// 4�L�[
				///</summary>
				_key Key4;

				/// <summary>
				/// 5�L�[
				///</summary>
				_key Key5;

				/// <summary>
				/// 6�L�[
				///</summary>
				_key Key6;

				/// <summary>
				/// 7�L�[
				///</summary>
				_key Key7;

				/// <summary>
				/// 8�L�[
				///</summary>
				_key Key8;

				/// <summary>
				/// 9�L�[
				///</summary>
				_key Key9;

				/// <summary>
				/// 0�L�[
				///</summary>
				_key Key0;



				/// <summary>
				/// NumLock�L�[
				///</summary>
				_key Numlock;

				/// <summary>
				/// �e���L�[1�L�[
				///</summary>
				_key Num1;

				/// <summary>
				/// �e���L�[2�L�[
				///</summary>
				_key Num2;

				/// <summary>
				/// �e���L�[3�L�[
				///</summary>
				_key Num3;

				/// <summary>
				/// �e���L�[4�L�[
				///</summary>
				_key Num4;

				/// <summary>
				/// �e���L�[5�L�[
				///</summary>
				_key Num5;

				/// <summary>
				/// �e���L�[6�L�[
				///</summary>
				_key Num6;

				/// <summary>
				/// �e���L�[7�L�[
				///</summary>
				_key Num7;

				/// <summary>
				/// �e���L�[8�L�[
				///</summary>
				_key Num8;

				/// <summary>
				/// �e���L�[9�L�[
				///</summary>
				_key Num9;

				/// <summary>
				/// �e���L�[0�L�[
				///</summary>
				_key Num0;

				/// <summary>
				/// �e���L�[*�L�[
				///</summary>
				_key NumAsterisk;

				/// <summary>
				/// �e���L�[+�L�[
				///</summary>
				_key NumPlus;

				/// <summary>
				/// �e���L�[-�L�[
				///</summary>
				_key NumMinus;

				/// <summary>
				/// �e���L�[.�L�[
				///</summary>
				_key NumPeriod;

				/// <summary>
				/// �e���L�[/�L�[
				///</summary>
				_key NumSlash;

				/// <summary>
				/// �e���L�[�̃G���^�[�L�[
				///</summary>
				_key NumEnter;



				/// <summary>
				/// -�L�[
				///</summary>
				_key Minus;

				/// <summary>
				/// \�L�[
				///</summary>
				_key Yen;

				/// <summary>
				/// ^�L�[
				///</summary>
				_key Caret;
				/// .<summary>
				/// �L�[
				///</summary>
				_key Period;

				/// <summary>
				/// �^�L�[
				///</summary>
				_key Slash;

				/// <summary>
				/// ��Alt�L�[
				///</summary>
				_key LAlt;

				/// <summary>
				/// �EAlt�L�[
				///</summary>
				_key RAlt;

				/// <summary>
				/// ScrollLock�L�[
				///</summary>
				_key ScrollLock;

				/// <summary>
				/// ;�L�[
				///</summary>
				_key Semicolon;

				/// <summary>
				/// :�L�[
				///</summary>
				_key Colon;

				/// <summary>
				/// [�L�[
				///</summary>
				_key LBracket;

				/// <summary>
				/// ]�L�[
				///</summary>
				_key RBracket;

				/// <summary>
				/// @�L�[
				///</summary>
				_key At;

				/// <summary>
				/// �_�L�[
				///</summary>
				_key Backslash;

				/// <summary>
				/// ,�L�[
				///</summary>
				_key Comma;

				/// <summary>
				/// �����L�[
				///</summary>
				_key Kanji;

				/// <summary>
				/// �ϊ��L�[
				///</summary>
				_key Convert;

				/// <summary>
				/// ���ϊ��L�[
				///</summary>
				_key NoConvert;

				/// <summary>
				/// ���ȃL�[
				///</summary>
				_key Kana;

				/// <summary>
				/// �A�v���P�[�V�������j���[�L�[
				///</summary>
				_key Menu;

				/// <summary>
				/// CapsLock�L�[
				///</summary>
				_key Capaslock;

				/// <summary>
				/// PrintScreen�L�[
				///</summary>
				_key Printscreen;

				/// <summary>
				/// PauseBreak�L�[
				///</summary>
				_key PauseBreak;

				/// <summary>
				/// ��Windows�L�[
				///</summary>
				_key LWindows;

				/// <summary>
				/// �EWindows�L�[
				///</summary>
				_key RWindows;



				/// <summary>
				/// �^�u�L�[
				///</summary>
				_key Tab;

				/// <summary>
				/// �o�b�N�X�y�[�X�L�[
				///</summary>
				_key Back;

				/// <summary>
				/// �G���^�[�L�[
				///</summary>
				_key Return;

				/// <summary>
				/// ���V�t�g�L�[
				///</summary>
				_key LShift;

				/// <summary>
				/// �E�V�t�g�L�[
				///</summary>
				_key RShift;

				/// <summary>
				/// ���R���g���[���L�[
				///</summary>
				_key LControl;

				/// <summary>
				/// �E�R���g���[���L�[
				///</summary>
				_key RControl;

				/// <summary>
				/// �G�X�P�[�v�L�[
				///</summary>
				_key Escape;

				/// <summary>
				/// �X�y�[�X�L�[
				///</summary>
				_key Space;

				/// <summary>
				/// PageUp�L�[
				///</summary>
				_key PageUp;

				/// <summary>
				///�ς�Down �L�[
				///</summary>
				_key PageDown;

				/// <summary>
				/// End�L�[
				///</summary>
				_key End;

				/// <summary>
				/// Home�L�[
				///</summary>
				_key Home;

				/// <summary>
				/// ���L�[
				///</summary>
				_key Left;

				/// <summary>
				/// ���L�[
				///</summary>
				_key Up;

				/// <summary>
				/// ���L�[
				///</summary>
				_key Right;

				/// <summary>
				/// ���L�[
				///</summary>
				_key Down;

				/// <summary>
				/// Insert�L�[
				///</summary>
				_key Insert;

				/// <summary>
				/// Delete�L�[
				///</summary>
				_key Delete;



				/// <summary>
				/// F1�L�[
				///</summary>
				_key F1;

				/// <summary>
				/// F2�L�[
				///</summary>
				_key F2;

				/// <summary>
				/// F3�L�[
				///</summary>
				_key F3;

				/// <summary>
				/// F4�L�[
				///</summary>
				_key F4;

				/// <summary>
				/// F5�L�[
				///</summary>
				_key F5;

				/// <summary>
				/// F6�L�[
				///</summary>
				_key F6;

				/// <summary>
				/// F7�L�[
				///</summary>
				_key F7;

				/// <summary>
				/// F8�L�[
				///</summary>
				_key F8;

				/// <summary>
				/// F9�L�[
				///</summary>
				_key F9;

				/// <summary>
				/// !0�L�[
				///</summary>
				_key F10;

				/// <summary>
				/// F11�L�[
				///</summary>
				_key F11;

				/// <summary>
				/// F12�L�[
				///</summary>
				_key F12;



				/// <summary>
				/// A�L�[
				///</summary>
				_key A;

				/// <summary>
				/// B�L�[
				///</summary>
				_key B;

				/// <summary>
				/// C�L�[
				///</summary>
				_key C;

				/// <summary>
				/// D�L�[
				///</summary>
				_key D;

				/// <summary>
				/// E�L�[
				///</summary>
				_key E;

				/// <summary>
				/// F�L�[
				///</summary>
				_key F;

				/// <summary>
				/// G�L�[
				///</summary>
				_key G;

				/// <summary>
				/// H�L�[
				///</summary>
				_key H;

				/// <summary>
				/// I�L�[
				///</summary>
				_key I;

				/// <summary>
				/// J�L�[
				///</summary>
				_key J;

				/// <summary>
				/// K�L�[
				///</summary>
				_key K;

				/// <summary>
				/// L�L�[
				///</summary>
				_key L;

				/// <summary>
				/// M�L�[
				///</summary>
				_key M;

				/// <summary>
				/// N�L�[
				///</summary>
				_key N;

				/// <summary>
				/// O�L�[
				///</summary>
				_key O;

				/// <summary>
				/// P�L�[
				///</summary>
				_key P;

				/// <summary>
				/// Q�L�[
				///</summary>
				_key Q;

				/// <summary>
				/// R�L�[
				///</summary>
				_key R;

				/// <summary>
				/// S�L�[
				///</summary>
				_key S;

				/// <summary>
				/// T�L�[
				///</summary>
				_key T;

				/// <summary>
				/// U�L�[
				///</summary>
				_key U;

				/// <summary>
				/// V�L�[
				///</summary>
				_key V;

				/// <summary>
				/// W�L�[
				///</summary>
				_key W;

				/// <summary>
				/// X�L�[
				///</summary>
				_key X;

				/// <summary>
				/// Y�L�[
				///</summary>
				_key Y;

				/// <summary>
				/// Z�L�[
				///</summary>
				_key Z;

				/// <summary>
				/// �L�[�{�[�h�̍X�V ���ʂ͎g�p���Ȃ�
				/// </summary>
				void update();
			};

			struct mouse {
			private:
				//LPSTR _cursor_type = IDC_ARROW;
			public:
				mouse();

				/// <summary>
				/// ���{�^��
				/// </summary>
				_mouse Left;

				/// <summary>
				/// ���{�^��
				/// </summary>
				_mouse Middle;

				/// <summary>
				/// �E�{�^��
				/// </summary>
				_mouse Right;

				_mouse Button4;
				_mouse Button5;
				_mouse Button6;
				_mouse Button7;
				_mouse Button8;

				/// <summary>
				/// �}�E�X�J�[�\���̈ʒu���擾
				/// </summary>
				/// <returns>�J�[�\���̈ʒu</returns>
				point<int> position() const;

				/// <summary>
				/// �}�E�X�J�[�\���̈ʒu��ݒ�
				/// </summary>
				/// <param name="p">�J�[�\���̈ʒu</param>
				void position(const point<int>& p);

				//LPSTR type() const;
				//void type(LPSTR type);

				/// <summary>
				/// �}�E�X�̍X�V ���ʂ͎g�p���Ȃ�
				/// </summary>
				void update();
			};
		}
	}
}