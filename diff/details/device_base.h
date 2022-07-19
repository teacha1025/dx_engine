#pragma once
namespace dx_engine {
	namespace detail {
		enum class device_state {
			press,
			release,
			up,
			down
		};

		class _device_base {
		protected:
			unsigned int _code = 0;
			unsigned int _press_count = 0;
			device_state _state = device_state::release;
		public:
			void update(const char key[]) {};

			unsigned int count() const;

			bool press() const;

			bool release() const;

			bool up() const;

			bool down() const;
		};
	}
}