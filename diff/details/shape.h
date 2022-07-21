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
}