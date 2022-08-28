#pragma once
#include "device_base.h"
namespace dx_engine {
	namespace detail {
		class _key : public input_base {
		public:
			_key(const unsigned int Code);
			_key() {}
			void update(const char key[]);
		};
	}
}