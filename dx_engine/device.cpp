#include <DxLib.h>
#include "key.h"
#include "device.h"
#include "point.h"

namespace dx_engine {
	namespace detail {
		namespace device {
			keyboard::keyboard() {
				A = _key(KEY_INPUT_A);
				B = _key(KEY_INPUT_B);
				C = _key(KEY_INPUT_C);
				D = _key(KEY_INPUT_D);
				E = _key(KEY_INPUT_E);
				F = _key(KEY_INPUT_F);
				G = _key(KEY_INPUT_G);
				H = _key(KEY_INPUT_H);
				I = _key(KEY_INPUT_I);
				J = _key(KEY_INPUT_J);
				K = _key(KEY_INPUT_K);
				L = _key(KEY_INPUT_L);
				N = _key(KEY_INPUT_N);
				M = _key(KEY_INPUT_M);
				O = _key(KEY_INPUT_O);
				P = _key(KEY_INPUT_P);
				Q = _key(KEY_INPUT_Q);
				R = _key(KEY_INPUT_R);
				S = _key(KEY_INPUT_S);
				T = _key(KEY_INPUT_T);
				U = _key(KEY_INPUT_U);
				V = _key(KEY_INPUT_V);
				W = _key(KEY_INPUT_W);
				X = _key(KEY_INPUT_X);
				Y = _key(KEY_INPUT_Y);
				Z = _key(KEY_INPUT_Z);
				Key1 = _key(KEY_INPUT_1);
				Key2 = _key(KEY_INPUT_2);
				Key3 = _key(KEY_INPUT_3);
				Key4 = _key(KEY_INPUT_4);
				Key5 = _key(KEY_INPUT_5);
				Key6 = _key(KEY_INPUT_6);
				Key7 = _key(KEY_INPUT_7);
				Key8 = _key(KEY_INPUT_8);
				Key9 = _key(KEY_INPUT_9);
				Key0 = _key(KEY_INPUT_0);
				F1 = _key(KEY_INPUT_F1);
				F2 = _key(KEY_INPUT_F2);
				F3 = _key(KEY_INPUT_F3);
				F4 = _key(KEY_INPUT_F4);
				F5 = _key(KEY_INPUT_F5);
				F6 = _key(KEY_INPUT_F6);
				F7 = _key(KEY_INPUT_F7);
				F8 = _key(KEY_INPUT_F8);
				F9 = _key(KEY_INPUT_F9);
				F10 = _key(KEY_INPUT_F10);
				F11 = _key(KEY_INPUT_F11);
				F12 = _key(KEY_INPUT_F12);
				Numlock = _key(KEY_INPUT_NUMLOCK);
				Num1 = _key(KEY_INPUT_NUMPAD1);
				Num2 = _key(KEY_INPUT_NUMPAD2);
				Num3 = _key(KEY_INPUT_NUMPAD3);
				Num4 = _key(KEY_INPUT_NUMPAD4);
				Num5 = _key(KEY_INPUT_NUMPAD5);
				Num6 = _key(KEY_INPUT_NUMPAD6);
				Num7 = _key(KEY_INPUT_NUMPAD7);
				Num8 = _key(KEY_INPUT_NUMPAD8);
				Num9 = _key(KEY_INPUT_NUMPAD9);
				Num0 = _key(KEY_INPUT_NUMPAD0);
				NumAsterisk = _key(KEY_INPUT_MULTIPLY);
				NumPlus = _key(KEY_INPUT_ADD);
				NumMinus = _key(KEY_INPUT_SUBTRACT);
				NumPeriod = _key(KEY_INPUT_DECIMAL);
				NumSlash = _key(KEY_INPUT_DIVIDE);
				NumEnter = _key(KEY_INPUT_NUMPADENTER);
				Minus = _key(KEY_INPUT_MINUS);
				Yen = _key(KEY_INPUT_YEN);
				Caret = _key(KEY_INPUT_PREVTRACK);
				Period = _key(KEY_INPUT_PERIOD);
				Slash = _key(KEY_INPUT_SLASH);
				LAlt = _key(KEY_INPUT_LALT);
				RAlt = _key(KEY_INPUT_RALT);
				ScrollLock = _key(KEY_INPUT_SCROLL);
				Semicolon = _key(KEY_INPUT_SEMICOLON);
				Colon = _key(KEY_INPUT_COLON);
				LBracket = _key(KEY_INPUT_LBRACKET);
				RBracket = _key(KEY_INPUT_RBRACKET);
				At = _key(KEY_INPUT_AT);
				Backslash = _key(KEY_INPUT_BACKSLASH);
				Comma = _key(KEY_INPUT_COMMA);
				Kanji = _key(KEY_INPUT_KANJI);
				Convert = _key(KEY_INPUT_CONVERT);
				NoConvert = _key(KEY_INPUT_NOCONVERT);
				Kana = _key(KEY_INPUT_KANA);
				Menu = _key(KEY_INPUT_APPS);
				Capaslock = _key(KEY_INPUT_CAPSLOCK);
				Printscreen = _key(KEY_INPUT_SYSRQ);
				PauseBreak = _key(KEY_INPUT_PAUSE);
				LWindows = _key(KEY_INPUT_LWIN);
				RWindows = _key(KEY_INPUT_RWIN);
				Tab = _key(KEY_INPUT_TAB);
				Back = _key(KEY_INPUT_BACK);
				Return = _key(KEY_INPUT_RETURN);
				LShift = _key(KEY_INPUT_LSHIFT);
				RShift = _key(KEY_INPUT_RSHIFT);
				LControl = _key(KEY_INPUT_LCONTROL);
				RControl = _key(KEY_INPUT_RCONTROL);
				Escape = _key(KEY_INPUT_ESCAPE);
				Space = _key(KEY_INPUT_SPACE);
				PageUp = _key(KEY_INPUT_PGUP);
				PageDown = _key(KEY_INPUT_PGDN);
				End = _key(KEY_INPUT_END);
				Home = _key(KEY_INPUT_HOME);
				Left = _key(KEY_INPUT_LEFT);
				Up = _key(KEY_INPUT_UP);
				Right = _key(KEY_INPUT_RIGHT);
				Down = _key(KEY_INPUT_DOWN);
				Insert = _key(KEY_INPUT_INSERT);
				Delete = _key(KEY_INPUT_DELETE);
			}

			void keyboard::update() {
				char isKey[256];
				GetHitKeyStateAll(isKey);

				A.update(isKey);
				B.update(isKey);
				C.update(isKey);
				D.update(isKey);
				E.update(isKey);
				F.update(isKey);
				G.update(isKey);
				H.update(isKey);
				I.update(isKey);
				J.update(isKey);
				K.update(isKey);
				L.update(isKey);
				N.update(isKey);
				M.update(isKey);
				O.update(isKey);
				P.update(isKey);
				Q.update(isKey);
				R.update(isKey);
				S.update(isKey);
				T.update(isKey);
				U.update(isKey);
				V.update(isKey);
				W.update(isKey);
				X.update(isKey);
				Y.update(isKey);
				Z.update(isKey);
				Key1.update(isKey);
				Key2.update(isKey);
				Key3.update(isKey);
				Key4.update(isKey);
				Key5.update(isKey);
				Key6.update(isKey);
				Key7.update(isKey);
				Key8.update(isKey);
				Key9.update(isKey);
				Key0.update(isKey);
				F1.update(isKey);
				F2.update(isKey);
				F3.update(isKey);
				F4.update(isKey);
				F5.update(isKey);
				F6.update(isKey);
				F7.update(isKey);
				F8.update(isKey);
				F9.update(isKey);
				F10.update(isKey);
				F11.update(isKey);
				F12.update(isKey);
				Numlock.update(isKey);
				Num1.update(isKey);
				Num2.update(isKey);
				Num3.update(isKey);
				Num4.update(isKey);
				Num5.update(isKey);
				Num6.update(isKey);
				Num7.update(isKey);
				Num8.update(isKey);
				Num9.update(isKey);
				Num0.update(isKey);
				NumAsterisk.update(isKey);
				NumPlus.update(isKey);
				NumMinus.update(isKey);
				NumPeriod.update(isKey);
				NumSlash.update(isKey);
				NumEnter.update(isKey);

				Minus.update(isKey);
				Yen.update(isKey);
				Caret.update(isKey);
				Period.update(isKey);
				Slash.update(isKey);
				LAlt.update(isKey);
				RAlt.update(isKey);
				ScrollLock.update(isKey);
				Semicolon.update(isKey);
				Colon.update(isKey);
				LBracket.update(isKey);
				RBracket.update(isKey);
				At.update(isKey);
				Backslash.update(isKey);
				Comma.update(isKey);
				Kanji.update(isKey);
				Convert.update(isKey);
				NoConvert.update(isKey);
				Kana.update(isKey);
				Menu.update(isKey);
				Capaslock.update(isKey);
				Printscreen.update(isKey);
				PauseBreak.update(isKey);
				LWindows.update(isKey);
				RWindows.update(isKey);

				Tab.update(isKey);
				Back.update(isKey);
				Return.update(isKey);
				LShift.update(isKey);
				RShift.update(isKey);
				LControl.update(isKey);
				RControl.update(isKey);
				Escape.update(isKey);
				Space.update(isKey);
				PageUp.update(isKey);
				PageDown.update(isKey);
				End.update(isKey);
				Home.update(isKey);
				Left.update(isKey);
				Up.update(isKey);
				Right.update(isKey);
				Down.update(isKey);
				Insert.update(isKey);
				Delete.update(isKey);

			}


			mouse::mouse() {
				Left = _mouse(MOUSE_INPUT_LEFT);
				Middle = _mouse(MOUSE_INPUT_MIDDLE);
				Right = _mouse(MOUSE_INPUT_RIGHT);
				Button4 = _mouse(MOUSE_INPUT_4);
				Button5 = _mouse(MOUSE_INPUT_5);
				Button6 = _mouse(MOUSE_INPUT_6);
				Button7 = _mouse(MOUSE_INPUT_7);
				Button8 = _mouse(MOUSE_INPUT_8);
			}

			point<unsigned int> mouse::position() const {
				point<int> p;
				GetMousePoint(&p.x, &p.y);
				return { (unsigned int)p.x, (unsigned int)p.y };
			}

			void mouse::update() {
				auto input = GetMouseInput();
				Left.update(input);
				Middle.update(input);
				Right.update(input);
				Button4.update(input);
				Button5.update(input);
				Button6.update(input);
				Button7.update(input);
				Button8.update(input);
			}
		}
	}
}