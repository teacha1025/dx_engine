#pragma once
#include <memory>
namespace dx_engine {
	namespace detail {
		enum class device_state {
			press,
			release,
			up,
			down
		};

		class input_base {
		protected:
			unsigned int _code = 0;
			unsigned int _press_count = 0;
			device_state _state = device_state::release;
		public:
			/// <summary>
			/// 押された時間の取得
			/// </summary>
			/// <returns>キーやボタンが押されたフレーム数</returns>
			unsigned int count() const;

			/// <summary>
			/// 押されているかどうかの取得
			/// </summary>
			/// <returns>押されているかどうか</returns>
			bool press() const;

			/// <summary>
			/// 離されているのかどうかの取得
			/// </summary>
			/// <returns>離されているかどうか</returns>
			bool release() const;

			/// <summary>
			/// 離されたかどうかの取得
			/// </summary>
			/// <returns>離された瞬間かどうか</returns>
			bool up() const;

			/// <summary>
			/// 押されたかどうかの取得
			/// </summary>
			/// <returns>押された瞬間かどうか</returns>
			bool down() const;
		};
		class _key;
		class _mouse;
	}
	
	/// <summary>
	/// 様々な入力の組み合わせを持つ入力クラス
	/// </summary>
	class inputs {
	public:
		
	private:
		using device = detail::input_base;
		using p_input = std::shared_ptr<inputs>;
		device* _dev = nullptr;
		p_input _left = nullptr, _right = nullptr;
		bool _is_or = true;
		friend inline inputs operator | (detail::_key& l, detail::_key& r);
		friend inline inputs operator | (detail::_mouse& l, detail::_mouse& r);
		friend inline inputs operator | (detail::_key& l, detail::_mouse& r);
		friend inline inputs operator | (detail::_mouse& l, detail::_key& r);
		friend inline inputs operator | (detail::_key& l, inputs r);
		friend inline inputs operator | (detail::_mouse& l, inputs r);

		friend inline inputs operator & (detail::_key& l, detail::_key& r);
		friend inline inputs operator & (detail::_mouse& l, detail::_mouse& r);
		friend inline inputs operator & (detail::_key& l, detail::_mouse& r);
		friend inline inputs operator & (detail::_mouse& l, detail::_key& r);
		friend inline inputs operator & (detail::_key& l, inputs r);
		friend inline inputs operator & (detail::_mouse& l, inputs r);

	public:
		inputs() = default;
		
		/// <summary>
			/// 押された時間の取得
			/// </summary>
			/// <returns>キーやボタンが押されたフレーム数</returns>
		unsigned int count() const;

		/// <summary>
		/// 押されているかどうかの取得
		/// </summary>
		/// <returns>押されているかどうか</returns>
		bool press() const;

		/// <summary>
		/// 離されているのかどうかの取得
		/// </summary>
		/// <returns>離されているかどうか</returns>
		bool release() const;

		/// <summary>
		/// 離されたかどうかの取得
		/// </summary>
		/// <returns>離された瞬間かどうか</returns>
		bool up() const;

		/// <summary>
		/// 押されたかどうかの取得
		/// </summary>
		/// <returns>押された瞬間かどうか</returns>
		bool down() const;

		inputs operator | (detail::_key& r) const;
		inputs operator | (detail::_mouse& r) const;
		inputs operator | (inputs r) const;
		inputs operator & (detail::_key& r) const;
		inputs operator & (detail::_mouse& r) const;
		inputs operator & (inputs r) const;

		/// <summary>
		/// キーボードから入力を作成
		/// </summary>
		/// <param name="key">キー</param>
		inputs(detail::_key& key);
		/// <summary>
		/// マウスのボタンから入力を作成
		/// </summary>
		/// <param name="mouse">マウスのボタン</param>
		inputs(detail::_mouse& mouse);
		/// <summary>
		/// ほかの入力から入力を作成
		/// </summary>
		/// <param name="input">ほかの入力</param>
		inputs(const inputs& input);
	};
	
	
	inputs operator | (detail::_key& l, detail::_key& r) {
		inputs i;
		i._left = std::make_shared<inputs>();
		i._left->_dev = reinterpret_cast<inputs::device*>(&l);
		i._right = std::make_shared<inputs>();
		i._right->_dev = reinterpret_cast<inputs::device*>(&r);
		i._is_or = true;
		return i;
	}
	inputs operator & (detail::_key& l, detail::_key& r) {
		inputs i;
		i._left = std::make_shared<inputs>();
		i._left->_dev = reinterpret_cast<inputs::device*>(&l);
		i._right = std::make_shared<inputs>();
		i._right->_dev = reinterpret_cast<inputs::device*>(&r);
		i._is_or = false;
		return i;
	}
	inputs operator | (detail::_mouse& l, detail::_mouse& r) {
		inputs i;
		i._left = std::make_shared<inputs>();
		i._left->_dev = reinterpret_cast<inputs::device*>(&l);
		i._right = std::make_shared<inputs>();
		i._right->_dev = reinterpret_cast<inputs::device*>(&r);
		i._is_or = true;
		return i;
	}
	inputs operator & (detail::_mouse& l, detail::_mouse& r) {
		inputs i;
		i._left = std::make_shared<inputs>();
		i._left->_dev = reinterpret_cast<inputs::device*>(&l);
		i._right = std::make_shared<inputs>();
		i._right->_dev = reinterpret_cast<inputs::device*>(&r);
		i._is_or = false;
		return i;
	}
	inputs operator | (detail::_key& l, detail::_mouse& r) {
		inputs i;
		i._left = std::make_shared<inputs>();
		i._left->_dev = reinterpret_cast<inputs::device*>(&l);
		i._right = std::make_shared<inputs>();
		i._right->_dev = reinterpret_cast<inputs::device*>(&r);
		i._is_or = true;
		return i;
	}
	inputs operator & (detail::_key& l, detail::_mouse& r) {
		inputs i;
		i._left = std::make_shared<inputs>();
		i._left->_dev = reinterpret_cast<inputs::device*>(&l);
		i._right = std::make_shared<inputs>();
		i._right->_dev = reinterpret_cast<inputs::device*>(&r);
		i._is_or = false;
		return i;
	}
	inputs operator | (detail::_mouse& l, detail::_key& r) {
		inputs i;
		i._left = std::make_shared<inputs>();
		i._left->_dev = reinterpret_cast<inputs::device*>(&l);
		i._right = std::make_shared<inputs>();
		i._right->_dev = reinterpret_cast<inputs::device*>(&r);
		i._is_or = true;
		return i;
	}
	inputs operator & (detail::_mouse& l, detail::_key& r) {
		inputs i;
		i._left = std::make_shared<inputs>();
		i._left->_dev = reinterpret_cast<inputs::device*>(&l);
		i._right = std::make_shared<inputs>();
		i._right->_dev = reinterpret_cast<inputs::device*>(&r);
		i._is_or = false;
		return i;
	}



	inputs operator | (detail::_key& l, inputs r) {
		inputs i;
		i._left = std::make_shared<inputs>();
		i._left->_dev = r._dev;
		i._left->_left = r._left;
		i._left->_right = r._right;
		i._left->_is_or = r._is_or;
		i._right = std::make_shared<inputs>();
		i._right->_dev = reinterpret_cast<inputs::device*>(&r);
		i._is_or = true;
		return i;
	}
	inputs operator & (detail::_key& l, inputs r) {
		inputs i;
		i._left = std::make_shared<inputs>();
		i._left->_dev = r._dev;
		i._left->_left = r._left;
		i._left->_right = r._right;
		i._left->_is_or = r._is_or;
		i._right = std::make_shared<inputs>();
		i._right->_dev = reinterpret_cast<inputs::device*>(&r);
		i._is_or = false;
		return i;
	}
	inputs operator | (detail::_mouse& l, inputs r) {
		inputs i;
		i._left = std::make_shared<inputs>();
		i._left->_dev = r._dev;
		i._left->_left = r._left;
		i._left->_right = r._right;
		i._left->_is_or = r._is_or;
		i._right = std::make_shared<inputs>();
		i._right->_dev = reinterpret_cast<inputs::device*>(&r);
		i._is_or = true;
		return i;
	}
	inputs operator & (detail::_mouse& l, inputs r) {
		inputs i;
		i._right = std::make_shared<inputs>();
		i._right->_dev = r._dev;
		i._right->_left = r._left;
		i._right->_right = r._right;
		i._right->_is_or = r._is_or;
		i._left = std::make_shared<inputs>();
		i._left->_dev = reinterpret_cast<inputs::device*>(&r);
		i._is_or = false;
		return i;
	}
}