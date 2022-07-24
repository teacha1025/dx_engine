#pragma once
#include "details.h"
#include "point.h"

namespace dx_engine {
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
	public:
		line& at(const std::vector<point<float>>& point);
		line& blend(dx_engine::blend mode, range<0, 255> param);
		line& filter(dx_engine::filter mode);
		line& colored(const color& color);
		line& thick(float thick);

		void draw();
		std::vector<point<float>> position() const;
	};
}