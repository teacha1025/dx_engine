#pragma once
#include <DxLib.h>
#include "point.h"
#include "vector.h"
#include "color.h"

namespace dx_engine {
	enum class blend {
		alpha	 = DX_BLENDMODE_ALPHA,
		add		 = DX_BLENDMODE_ADD,
		sub		 = DX_BLENDMODE_SUB,
		inv_src  = DX_BLENDMODE_INVSRC,
		inv_dest = DX_BLENDMODE_INVDESTCOLOR,
	};


	namespace detail {
		class _system {
		private:

		public:
			bool update();
			~_system();
		};

		class _window {
		private:
			point<UINT> _size = {1280, 960};
		public:
			void size(const point<UINT>& size);
			point<UINT> size() const;
		};

		class shape {
		protected:
			point<float> _position, _center;
			float _angle = 0;
			color _color;
			blend _blend = blend::alpha;
			byte _blendparam = 255;
		public:
			shape& centered(const point<float>& center);
			shape& rotateed(float angle);
			shape& colored(const color& color);
			shape& blend(blend mode, int param);
			shape& at(const point<float>& position);

			point<float> position() const;

			void move(const point<float>& value);

			virtual void draw() = 0;
		};
	}

	class rect : public detail::shape {
	private:
		point<float> _size;
	public:
		rect(const point<float> size);

		point<float> size() const;
		void resize(const point<float>& size);

		void draw() override;
	};

	extern detail::_system system;
	extern detail::_window window;
}