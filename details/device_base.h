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
			/// �����ꂽ���Ԃ̎擾
			/// </summary>
			/// <returns>�L�[��{�^���������ꂽ�t���[����</returns>
			unsigned int count() const;

			/// <summary>
			/// ������Ă��邩�ǂ����̎擾
			/// </summary>
			/// <returns>������Ă��邩�ǂ���</returns>
			bool press() const;

			/// <summary>
			/// ������Ă���̂��ǂ����̎擾
			/// </summary>
			/// <returns>������Ă��邩�ǂ���</returns>
			bool release() const;

			/// <summary>
			/// �����ꂽ���ǂ����̎擾
			/// </summary>
			/// <returns>�����ꂽ�u�Ԃ��ǂ���</returns>
			bool up() const;

			/// <summary>
			/// �����ꂽ���ǂ����̎擾
			/// </summary>
			/// <returns>�����ꂽ�u�Ԃ��ǂ���</returns>
			bool down() const;
		};
		class _key;
		class _mouse;
	}
	
	/// <summary>
	/// �l�X�ȓ��͂̑g�ݍ��킹�������̓N���X
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
			/// �����ꂽ���Ԃ̎擾
			/// </summary>
			/// <returns>�L�[��{�^���������ꂽ�t���[����</returns>
		unsigned int count() const;

		/// <summary>
		/// ������Ă��邩�ǂ����̎擾
		/// </summary>
		/// <returns>������Ă��邩�ǂ���</returns>
		bool press() const;

		/// <summary>
		/// ������Ă���̂��ǂ����̎擾
		/// </summary>
		/// <returns>������Ă��邩�ǂ���</returns>
		bool release() const;

		/// <summary>
		/// �����ꂽ���ǂ����̎擾
		/// </summary>
		/// <returns>�����ꂽ�u�Ԃ��ǂ���</returns>
		bool up() const;

		/// <summary>
		/// �����ꂽ���ǂ����̎擾
		/// </summary>
		/// <returns>�����ꂽ�u�Ԃ��ǂ���</returns>
		bool down() const;

		inputs operator | (detail::_key& r) const;
		inputs operator | (detail::_mouse& r) const;
		inputs operator | (inputs r) const;
		inputs operator & (detail::_key& r) const;
		inputs operator & (detail::_mouse& r) const;
		inputs operator & (inputs r) const;

		/// <summary>
		/// �L�[�{�[�h������͂��쐬
		/// </summary>
		/// <param name="key">�L�[</param>
		inputs(detail::_key& key);
		/// <summary>
		/// �}�E�X�̃{�^��������͂��쐬
		/// </summary>
		/// <param name="mouse">�}�E�X�̃{�^��</param>
		inputs(detail::_mouse& mouse);
		/// <summary>
		/// �ق��̓��͂�����͂��쐬
		/// </summary>
		/// <param name="input">�ق��̓���</param>
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