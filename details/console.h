#pragma once
#include <string>
#include <vector>
#include "def.h"
#include "draw_param.h"
#include "point.h"
#include "vector.h"
#include "color.h"
#include "pallet.h"
#include "text.h"
#include "device.h"

namespace dx_engine {
	namespace detail {
		struct dbg {
			std::string text;
			color _color;
			dbg(std::string_view tex, const color& c) {
				text = tex;
				this->_color = c;
			}
		};

		class _console {
			std::vector<dbg> list, r_list;
			text f;
			color cl = pallet::white, cr = pallet::white;
			bool flag = false;
		public:
			/// <summary>
			/// �R���\�[���̏�����
			/// <para>�ʏ�g�p���Ȃ�</para>
			/// </summary>	
			/// <param name="windowsize">�E�B���h�E�̑傫��</param>
			void init(const point<uint>& windowsize);

			/// <summary>
			/// �R���\�[���̍X�V
			/// <para>�ʏ�g�p���Ȃ�</para>
			/// </summary>
			/// <param name="windowsize">�E�B���h�E�̑傫��</param>
			void update(const point<uint>& windowsize);

			/// <summary>
			/// �R���\�[���̃N���A
			/// <para>�ʏ�g�p���Ȃ�</para>
			/// </summary>
			void clear();

			/// <summary>
			/// �R���\�[���\���̐؂�ւ�
			/// </summary>
			/// <param name="flag">�\�����邩</param>
			void set(bool flag);

			/// <summary>
			/// �����̃R���\�[���ɒǉ�
			/// </summary>
			/// <param name="str">�ǉ����镶����</param>
			_console& operator << (const std::string& str) {
				if (!flag) return *this;
				list.push_back(dbg(str, cl));
				return *this;
			}
			/// <summary>
			/// �E���̃R���\�[���ɒǉ�
			/// </summary>
			/// <param name="str">�ǉ����镶����</param>
			_console& operator >> (const std::string& str) {
				if (!flag) return *this;
				r_list.push_back(dbg(str, cr));
				return *this;
			}

			/// <summary>
			/// �����̃R���\�[���ɒǉ�
			/// </summary>
			/// <param name="str">�ǉ����镶����</param>
			_console& operator << (const char str[]) {
				if (!flag) return *this;
				list.push_back(dbg(std::string(str), cl));
				return *this;
			}
			/// <summary>
			/// �E���̃R���\�[���ɒǉ�
			/// </summary>
			/// <param name="str">�ǉ����镶����</param>
			_console& operator >> (const char str[]) {
				if (!flag) return *this;
				r_list.push_back(dbg(std::string(str), cr));
				return *this;
			}

			/// <summary>
			/// �����̃R���\�[���̐F��ύX
			/// </summary>
			/// <param name="c">�ύX����F</param>
			_console& operator << (const color& c) {
				if (!flag) return *this;
				cl = c;
				return *this;
			}
			/// <summary>
			/// �E���̃R���\�[���̐F��ύX
			/// </summary>
			/// <param name="c">�ύX����F</param>
			_console& operator >> (const color& c) {
				if (!flag) return *this;
				cr = c;
				return *this;
			}

			/// <summary>
			/// �����̃R���\�[���ɒǉ�
			/// </summary>
			/// <param name="b">�ǉ�����t���O</param>
			_console& operator << (bool b) {
				if (!flag) return *this;
				list.push_back(dbg(b ? "true" : "false", cl));
				return *this;
			}
			/// <summary>
			/// �E���̃R���\�[���ɒǉ�
			/// </summary>
			/// <param name="b">�ǉ�����t���O</param>
			template <Number t>
			_console& operator >> (bool b) {
				if (!flag) return *this;
				r_list.push_back(dbg(b ? "true" : "false", cr));
				return *this;
			}

			/// <summary>
			/// �����̃R���\�[���ɒǉ�
			/// </summary>
			/// <param name="p">�ǉ�������W</param>
			template <Number t>
			_console& operator << (const point<t>& p) {
				if (!flag) return *this;
				list.push_back(dbg(p.to_string(), cl));
				return *this;
			}
			/// <summary>
			/// �E���̃R���\�[���ɒǉ�
			/// </summary>
			/// <param name="p">�ǉ�������W</param>
			template <Number t>
			_console& operator >> (const point<t>& p) {
				if (!flag) return *this;
				r_list.push_back(dbg(p.to_string(), cr));
				return *this;
			}

			/// <summary>
			/// �����̃R���\�[���ɒǉ�
			/// </summary>
			/// <param name="v">�ǉ����鐔�l</param>
			template <Number t>
			_console& operator << (t v) {
				if (!flag) return *this;
				list.push_back(dbg(std::to_string(v), cl));
				return *this;
			}
			/// <summary>
			/// �E���̃R���\�[���ɒǉ�
			/// </summary>
			/// <param name="v">�ǉ����鐔�l</param>
			template <Number t>
			_console& operator >> (t v) {
				if (!flag) return *this;
				r_list.push_back(dbg(std::to_string(v), cr));
				return *this;
			}
		};

	}
	/// <summary>
	/// ��ʏ�ɕ\������R���\�[��
	/// </summary>
	extern detail::_console console;
}