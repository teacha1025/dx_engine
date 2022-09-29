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
				/// 1キー
				///</summary>
				_key Key1;

				/// <summary>
				/// 2キー
				///</summary>
				_key Key2;

				/// <summary>
				/// 3キー
				///</summary>
				_key Key3;

				/// <summary>
				/// 4キー
				///</summary>
				_key Key4;

				/// <summary>
				/// 5キー
				///</summary>
				_key Key5;

				/// <summary>
				/// 6キー
				///</summary>
				_key Key6;

				/// <summary>
				/// 7キー
				///</summary>
				_key Key7;

				/// <summary>
				/// 8キー
				///</summary>
				_key Key8;

				/// <summary>
				/// 9キー
				///</summary>
				_key Key9;

				/// <summary>
				/// 0キー
				///</summary>
				_key Key0;



				/// <summary>
				/// NumLockキー
				///</summary>
				_key Numlock;

				/// <summary>
				/// テンキー1キー
				///</summary>
				_key Num1;

				/// <summary>
				/// テンキー2キー
				///</summary>
				_key Num2;

				/// <summary>
				/// テンキー3キー
				///</summary>
				_key Num3;

				/// <summary>
				/// テンキー4キー
				///</summary>
				_key Num4;

				/// <summary>
				/// テンキー5キー
				///</summary>
				_key Num5;

				/// <summary>
				/// テンキー6キー
				///</summary>
				_key Num6;

				/// <summary>
				/// テンキー7キー
				///</summary>
				_key Num7;

				/// <summary>
				/// テンキー8キー
				///</summary>
				_key Num8;

				/// <summary>
				/// テンキー9キー
				///</summary>
				_key Num9;

				/// <summary>
				/// テンキー0キー
				///</summary>
				_key Num0;

				/// <summary>
				/// テンキー*キー
				///</summary>
				_key NumAsterisk;

				/// <summary>
				/// テンキー+キー
				///</summary>
				_key NumPlus;

				/// <summary>
				/// テンキー-キー
				///</summary>
				_key NumMinus;

				/// <summary>
				/// テンキー.キー
				///</summary>
				_key NumPeriod;

				/// <summary>
				/// テンキー/キー
				///</summary>
				_key NumSlash;

				/// <summary>
				/// テンキーのエンターキー
				///</summary>
				_key NumEnter;



				/// <summary>
				/// -キー
				///</summary>
				_key Minus;

				/// <summary>
				/// \キー
				///</summary>
				_key Yen;

				/// <summary>
				/// ^キー
				///</summary>
				_key Caret;
				/// .<summary>
				/// キー
				///</summary>
				_key Period;

				/// <summary>
				/// ／キー
				///</summary>
				_key Slash;

				/// <summary>
				/// 左Altキー
				///</summary>
				_key LAlt;

				/// <summary>
				/// 右Altキー
				///</summary>
				_key RAlt;

				/// <summary>
				/// ScrollLockキー
				///</summary>
				_key ScrollLock;

				/// <summary>
				/// ;キー
				///</summary>
				_key Semicolon;

				/// <summary>
				/// :キー
				///</summary>
				_key Colon;

				/// <summary>
				/// [キー
				///</summary>
				_key LBracket;

				/// <summary>
				/// ]キー
				///</summary>
				_key RBracket;

				/// <summary>
				/// @キー
				///</summary>
				_key At;

				/// <summary>
				/// ＼キー
				///</summary>
				_key Backslash;

				/// <summary>
				/// ,キー
				///</summary>
				_key Comma;

				/// <summary>
				/// 漢字キー
				///</summary>
				_key Kanji;

				/// <summary>
				/// 変換キー
				///</summary>
				_key Convert;

				/// <summary>
				/// 無変換キー
				///</summary>
				_key NoConvert;

				/// <summary>
				/// かなキー
				///</summary>
				_key Kana;

				/// <summary>
				/// アプリケーションメニューキー
				///</summary>
				_key Menu;

				/// <summary>
				/// CapsLockキー
				///</summary>
				_key Capaslock;

				/// <summary>
				/// PrintScreenキー
				///</summary>
				_key Printscreen;

				/// <summary>
				/// PauseBreakキー
				///</summary>
				_key PauseBreak;

				/// <summary>
				/// 左Windowsキー
				///</summary>
				_key LWindows;

				/// <summary>
				/// 右Windowsキー
				///</summary>
				_key RWindows;



				/// <summary>
				/// タブキー
				///</summary>
				_key Tab;

				/// <summary>
				/// バックスペースキー
				///</summary>
				_key Back;

				/// <summary>
				/// エンターキー
				///</summary>
				_key Return;

				/// <summary>
				/// 左シフトキー
				///</summary>
				_key LShift;

				/// <summary>
				/// 右シフトキー
				///</summary>
				_key RShift;

				/// <summary>
				/// 左コントロールキー
				///</summary>
				_key LControl;

				/// <summary>
				/// 右コントロールキー
				///</summary>
				_key RControl;

				/// <summary>
				/// エスケープキー
				///</summary>
				_key Escape;

				/// <summary>
				/// スペースキー
				///</summary>
				_key Space;

				/// <summary>
				/// PageUpキー
				///</summary>
				_key PageUp;

				/// <summary>
				///ぱげDown キー
				///</summary>
				_key PageDown;

				/// <summary>
				/// Endキー
				///</summary>
				_key End;

				/// <summary>
				/// Homeキー
				///</summary>
				_key Home;

				/// <summary>
				/// ←キー
				///</summary>
				_key Left;

				/// <summary>
				/// ↑キー
				///</summary>
				_key Up;

				/// <summary>
				/// →キー
				///</summary>
				_key Right;

				/// <summary>
				/// ↓キー
				///</summary>
				_key Down;

				/// <summary>
				/// Insertキー
				///</summary>
				_key Insert;

				/// <summary>
				/// Deleteキー
				///</summary>
				_key Delete;



				/// <summary>
				/// F1キー
				///</summary>
				_key F1;

				/// <summary>
				/// F2キー
				///</summary>
				_key F2;

				/// <summary>
				/// F3キー
				///</summary>
				_key F3;

				/// <summary>
				/// F4キー
				///</summary>
				_key F4;

				/// <summary>
				/// F5キー
				///</summary>
				_key F5;

				/// <summary>
				/// F6キー
				///</summary>
				_key F6;

				/// <summary>
				/// F7キー
				///</summary>
				_key F7;

				/// <summary>
				/// F8キー
				///</summary>
				_key F8;

				/// <summary>
				/// F9キー
				///</summary>
				_key F9;

				/// <summary>
				/// !0キー
				///</summary>
				_key F10;

				/// <summary>
				/// F11キー
				///</summary>
				_key F11;

				/// <summary>
				/// F12キー
				///</summary>
				_key F12;



				/// <summary>
				/// Aキー
				///</summary>
				_key A;

				/// <summary>
				/// Bキー
				///</summary>
				_key B;

				/// <summary>
				/// Cキー
				///</summary>
				_key C;

				/// <summary>
				/// Dキー
				///</summary>
				_key D;

				/// <summary>
				/// Eキー
				///</summary>
				_key E;

				/// <summary>
				/// Fキー
				///</summary>
				_key F;

				/// <summary>
				/// Gキー
				///</summary>
				_key G;

				/// <summary>
				/// Hキー
				///</summary>
				_key H;

				/// <summary>
				/// Iキー
				///</summary>
				_key I;

				/// <summary>
				/// Jキー
				///</summary>
				_key J;

				/// <summary>
				/// Kキー
				///</summary>
				_key K;

				/// <summary>
				/// Lキー
				///</summary>
				_key L;

				/// <summary>
				/// Mキー
				///</summary>
				_key M;

				/// <summary>
				/// Nキー
				///</summary>
				_key N;

				/// <summary>
				/// Oキー
				///</summary>
				_key O;

				/// <summary>
				/// Pキー
				///</summary>
				_key P;

				/// <summary>
				/// Qキー
				///</summary>
				_key Q;

				/// <summary>
				/// Rキー
				///</summary>
				_key R;

				/// <summary>
				/// Sキー
				///</summary>
				_key S;

				/// <summary>
				/// Tキー
				///</summary>
				_key T;

				/// <summary>
				/// Uキー
				///</summary>
				_key U;

				/// <summary>
				/// Vキー
				///</summary>
				_key V;

				/// <summary>
				/// Wキー
				///</summary>
				_key W;

				/// <summary>
				/// Xキー
				///</summary>
				_key X;

				/// <summary>
				/// Yキー
				///</summary>
				_key Y;

				/// <summary>
				/// Zキー
				///</summary>
				_key Z;

				/// <summary>
				/// キーボードの更新 普通は使用しない
				/// </summary>
				void update();
			};

			struct mouse {
			private:
				//LPSTR _cursor_type = IDC_ARROW;
			public:
				mouse();

				/// <summary>
				/// 左ボタン
				/// </summary>
				_mouse Left;

				/// <summary>
				/// 中ボタン
				/// </summary>
				_mouse Middle;

				/// <summary>
				/// 右ボタン
				/// </summary>
				_mouse Right;

				_mouse Button4;
				_mouse Button5;
				_mouse Button6;
				_mouse Button7;
				_mouse Button8;

				/// <summary>
				/// マウスカーソルの位置を取得
				/// </summary>
				/// <returns>カーソルの位置</returns>
				point<int> position() const;

				/// <summary>
				/// マウスカーソルの位置を設定
				/// </summary>
				/// <param name="p">カーソルの位置</param>
				void position(const point<int>& p);

				//LPSTR type() const;
				//void type(LPSTR type);

				/// <summary>
				/// マウスの更新 普通は使用しない
				/// </summary>
				void update();
			};
		}
	}
}