#pragma once
#include "details.h"
#include "point.h"

namespace dx_engine {
	namespace detail {
		class draw_object {
		protected:
			blend _blend = blend::alpha;
			byte _blendparam = 255;
			filter _filter = filter::nearest;
		public:
			virtual void draw() = 0;
		};

		class shape : public draw_object {
		protected:
			point<float> _position{}, _center{};
			float _angle = 0;
			float _thick = 1.0f;
			color _color;

			bool _fill_flag = true;
		public:
			virtual shape& centered(const dx_engine::point<float>& center);
			virtual shape& rotateed(float angle);
			virtual shape& colored(const color& color);
			virtual shape& blend(dx_engine::blend mode, range<0, 255> param);
			virtual shape& filter(filter mode);
			virtual shape& at(const dx_engine::point<float>& position);
			virtual shape& fill(bool flag);
			virtual shape& thick(float thick);

			virtual point<float> position() const;

			virtual void move(const dx_engine::point<float>& value);
		};
	}
	/*struct vertex_2d;
	namespace detail {
		struct uv {
			float u, v;
		};

		VERTEX2D convert_vertex2d(dx_engine::vertex_2d* vertex);
	}

	struct vertex_2d {
		point<float> pos;
		color color;
		detail::uv uv;
	};

	class polygon : public detail::draw_object {
	private:

	public:
		polygon& blend(dx_engine::blend mode, range<0, 255> param);
		polygon& filter(dx_engine::filter mode);
		virtual void draw() override;
	};*/

	class rect : public detail::shape {
	private:
		point<float> _size;
	public:
		rect();
		rect(const dx_engine::point<float> size);

		point<float> size() const;
		void resize(const dx_engine::point<float>& size);

		void draw() override;
	};

	class circle : public detail::shape {
	private:
		float _r;
	public:
		circle();
		circle(float r);

		float size() const;
		void resize(float r);

		void draw() override;
	};

	class line : public detail::draw_object{
	private:
		std::vector<point<float>> _position;
		float _thick = 1.0f;
		color _color;
		bool _round_edge = true;
	public:
		line& at(const std::vector<point<float>>& point);
		line& blend(dx_engine::blend mode, range<0, 255> param);
		line& filter(dx_engine::filter mode);
		line& colored(const color& color);
		line& thick(float thick);
		line& round(bool flag);

		void draw();
		std::vector<point<float>> position() const;
	};
}