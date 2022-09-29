#include "DxLib.h"
#include "../details/shape.h"
#include "../details/range.h"

namespace dx_engine {
	namespace detail {
		/*shape shape::centered(const point<double>& center)&& {
			_center = center;
			return std::move(*this);
		}
		shape shape::rotateed(double angle)&& {
			_angle = angle;
			return std::move(*this);
		}
		shape shape::colored(const color& color)&& {
			_color = color;
			return std::move(*this);
		}
		shape shape::blend(dx_engine::blend mode, range<0, 255> param) &&{
			_blend = mode;
			_blendparam = param;
			return std::move(*this);
		}
		shape shape::filter(dx_engine::filter mode) &&{
			_filter = mode;
			return std::move(*this);
		}
		shape shape::at(const point<double>& position) &&{
			_position = position;
			return std::move(*this);
		}
		shape shape::fill(bool flag)&& {
			_fill_flag = flag;
			return std::move(*this);
		}
		shape shape::thick(float thick)&& {
			_thick = thick;
			return std::move(*this);
		}
		shape shape::extended(double rate)&& {
			_rate = rate;
			return std::move(*this);
		}*/

		shape& shape::centered(const point<double>& center) {
			_center = center;
			return *this;
		}
		shape& shape::rotateed(double angle) {
			_angle = angle;
			return *this;
		}
		shape& shape::colored(const color& color) {
			_color = color;
			return *this;
		}
		shape& shape::blend(dx_engine::blend mode, range<0, 255> param) {
			_blend = mode;
			_blendparam = param;
			return *this;
		}
		shape& shape::filter(dx_engine::filter mode) {
			_filter = mode;
			return *this;
		}
		shape& shape::at(const point<double>& position) {
			_position = position;
			return *this;
		}
		shape& shape::fill(bool flag) {
			_fill_flag = flag;
			return *this;
		}
		shape& shape::thick(float thick) {
			_thick = thick;
			return *this;
		}
		shape& shape::extended(double rate) {
			_rate = rate;
			return *this;
		}

		point<double> shape::position() const{
			return _position;
		}

		point<double> shape::center() const {
			return _center;
		}

		double shape::rotate() const {
			return _angle;
		}

		void shape::move(const point<double>& value) {
			_position += value;
		}

		/*VERTEX2D convert_vertex2d(dx_engine::vertex_2d* vertex) {
			return VERTEX2D{ .pos{.x = vertex->pos.x, .y = vertex->pos.y, .z = 0},.rhw = 0.0f,.dif = GetColorU8(static_cast<int>(vertex->color.r),static_cast<int>(vertex->color.g),static_cast<int>(vertex->color.b),static_cast<int>(vertex->color.a)),.u = vertex->uv.u,.v = vertex->uv.v };
		}*/
	}
}