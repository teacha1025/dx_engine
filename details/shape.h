#pragma once
#include <tuple>
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
			point<double> _position{}, _center{};
			double _angle = 0;
			float _thick = 1.0f;
			color _color;

			bool _fill_flag = true;
		public:
			virtual shape& centered(const dx_engine::point<double>& center);
			virtual shape& rotateed(double angle);
			virtual shape& colored(const color& color);
			virtual shape& blend(dx_engine::blend mode, range<0, 255> param);
			virtual shape& filter(filter mode);
			virtual shape& at(const dx_engine::point<double>& position);
			virtual shape& fill(bool flag);
			virtual shape& thick(float thick);

			virtual point<double> position() const;
			virtual point<double> center() const;
			virtual double rotate() const;

			virtual void move(const dx_engine::point<double>& value);
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
	class line : public detail::draw_object {
	private:
		std::vector<point<double>> _position;
		float _thick = 1.0f;
		color _color;
		bool _round_edge = true;
	public:
		line& at(const std::vector<point<double>>& point);
		line& blend(dx_engine::blend mode, range<0, 255> param);
		line& filter(dx_engine::filter mode);
		line& colored(const color& color);
		line& thick(float thick);
		line& round(bool flag);

		void draw();
		std::vector<point<double>> position() const;
	};

	class rect : public detail::shape {
	private:
		point<double> _size;
	public:
		rect();
		rect(const dx_engine::point<double> size);

		point<double> size() const;
		void resize(const dx_engine::point<double>& size);

		void draw() override;

		std::tuple<point<double>, point<double>, point<double>, point<double>> verteces() const;

		line edge() const;
	};

	class circle : public detail::shape {
	private:
		double _r;
	public:
		circle();
		circle(double r);

		double size() const;
		void resize(double r);

		void draw() override;
	};

	
}