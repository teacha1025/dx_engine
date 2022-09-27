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
			/// コンソールの初期化
			/// <para>通常使用しない</para>
			/// </summary>	
			/// <param name="windowsize">ウィンドウの大きさ</param>
			void init(const point<uint>& windowsize);

			/// <summary>
			/// コンソールの更新
			/// <para>通常使用しない</para>
			/// </summary>
			/// <param name="windowsize">ウィンドウの大きさ</param>
			void update(const point<uint>& windowsize);

			/// <summary>
			/// コンソールのクリア
			/// <para>通常使用しない</para>
			/// </summary>
			void clear();

			/// <summary>
			/// コンソール表示の切り替え
			/// </summary>
			/// <param name="flag">表示するか</param>
			void set(bool flag);

			/// <summary>
			/// 左側のコンソールに追加
			/// </summary>
			/// <param name="str">追加する文字列</param>
			_console& operator << (const std::string& str) {
				if (!flag) return *this;
				list.push_back(dbg(str, cl));
				return *this;
			}
			/// <summary>
			/// 右側のコンソールに追加
			/// </summary>
			/// <param name="str">追加する文字列</param>
			_console& operator >> (const std::string& str) {
				if (!flag) return *this;
				r_list.push_back(dbg(str, cr));
				return *this;
			}

			/// <summary>
			/// 左側のコンソールに追加
			/// </summary>
			/// <param name="str">追加する文字列</param>
			_console& operator << (const char str[]) {
				if (!flag) return *this;
				list.push_back(dbg(std::string(str), cl));
				return *this;
			}
			/// <summary>
			/// 右側のコンソールに追加
			/// </summary>
			/// <param name="str">追加する文字列</param>
			_console& operator >> (const char str[]) {
				if (!flag) return *this;
				r_list.push_back(dbg(std::string(str), cr));
				return *this;
			}

			/// <summary>
			/// 左側のコンソールの色を変更
			/// </summary>
			/// <param name="c">変更する色</param>
			_console& operator << (const color& c) {
				if (!flag) return *this;
				cl = c;
				return *this;
			}
			/// <summary>
			/// 右側のコンソールの色を変更
			/// </summary>
			/// <param name="c">変更する色</param>
			_console& operator >> (const color& c) {
				if (!flag) return *this;
				cr = c;
				return *this;
			}

			/// <summary>
			/// 左側のコンソールに追加
			/// </summary>
			/// <param name="b">追加するフラグ</param>
			_console& operator << (bool b) {
				if (!flag) return *this;
				list.push_back(dbg(b ? "true" : "false", cl));
				return *this;
			}
			/// <summary>
			/// 右側のコンソールに追加
			/// </summary>
			/// <param name="b">追加するフラグ</param>
			template <Number t>
			_console& operator >> (bool b) {
				if (!flag) return *this;
				r_list.push_back(dbg(b ? "true" : "false", cr));
				return *this;
			}

			/// <summary>
			/// 左側のコンソールに追加
			/// </summary>
			/// <param name="p">追加する座標</param>
			template <Number t>
			_console& operator << (const point<t>& p) {
				if (!flag) return *this;
				list.push_back(dbg(p.to_string(), cl));
				return *this;
			}
			/// <summary>
			/// 右側のコンソールに追加
			/// </summary>
			/// <param name="p">追加する座標</param>
			template <Number t>
			_console& operator >> (const point<t>& p) {
				if (!flag) return *this;
				r_list.push_back(dbg(p.to_string(), cr));
				return *this;
			}

			/// <summary>
			/// 左側のコンソールに追加
			/// </summary>
			/// <param name="v">追加する数値</param>
			template <Number t>
			_console& operator << (t v) {
				if (!flag) return *this;
				list.push_back(dbg(std::to_string(v), cl));
				return *this;
			}
			/// <summary>
			/// 右側のコンソールに追加
			/// </summary>
			/// <param name="v">追加する数値</param>
			template <Number t>
			_console& operator >> (t v) {
				if (!flag) return *this;
				r_list.push_back(dbg(std::to_string(v), cr));
				return *this;
			}
		};

	}
	/// <summary>
	/// 画面上に表示するコンソール
	/// </summary>
	extern detail::_console console;
}