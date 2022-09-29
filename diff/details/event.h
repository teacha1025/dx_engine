#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include "def.h"
#include "range.h"


namespace dx_engine {
	/// <summary>
	/// �C�x���g�̌p�����̃N���X
	/// </summary>
	class event {
	public:
		/// <summary>
		/// �C�x���g�̍X�V
		/// </summary>
		/// <param name="count">�o�ߎ���</param>
		/// <returns>�C�x���g�𑱂��邩</returns>
		virtual bool update(uint count) = 0;
	};

	class event_manager {
	private:
		using func_type = std::function<bool(uint)>;
		using list_type = std::pair<func_type, uint>;
		std::vector<list_type> _event_list;

	public:
		/// <summary>
		/// �C�x���g�̒ǉ�
		/// </summary>
		/// <typeparam name="event_t">event�N���X���p�����ꂽ�N���X</typeparam>
		/// <typeparam name="...Args">event_t�̃R���X�g���N�^�̈���</typeparam>
		/// <param name="...args">event_t�̃R���X�g���N�^�̈���</param>
		template<class event_t, class... Args>
		void add(Args&&... args) {
			_event_list.push_back(std::make_pair(std::bind(&event::update, std::make_shared<event_t>(args...), std::placeholders::_1), 0));
		}

		/// <summary>
		/// �C�x���g�̒ǉ�
		/// </summary>
		/// <param name="func">�C�x���g�������ꂽ�֐��I�u�W�F�N�g</param>
		void add(func_type func);

		/// <summary>
		/// �C�x���g�̍X�V
		/// </summary>
		void update();
	};
}