#pragma once
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
		class _system final {
		private:
			ULONGLONG delta_msec = 0;
			float _fps;
		public:
			device::keyboard keyboard;
			device::mouse mouse;
			bool update();
			float delta_sec() const;
			double delta_sec_d() const;
			float fps() const;
			~_system();
		};

		class _window final {
		private:
			point<uint> _size = { 1280, 960 };
			//color _background;
			bool _fullscreen = false, _vsync = false;
			//std::string _title = "";
		public:
			void background(const color& bg);
			void title(const std::string& title);

			void size(const point<uint>& size);
			point<uint> size() const;
		};

		class shape {
		protected:
			point<float> _position{}, _center{};
			float _angle = 0;
			float _thick = 1.0f;
			color _color;
			blend _blend = blend::alpha;
			byte _blendparam = 255;
			bool _fill_flag = true;
		public:
			virtual shape& centered(const dx_engine::point<float>& center);
			virtual shape& rotateed(float angle);
			virtual shape& colored(const color& color);
			virtual shape& blend(dx_engine::blend mode, int param);
			virtual shape& at(const dx_engine::point<float>& position);
			virtual shape& fill(bool flag);
			virtual shape& thick(float thick);

			virtual point<float> position() const;

			virtual void move(const dx_engine::point<float>& value);

			virtual void draw() = 0;
		};
	}
}