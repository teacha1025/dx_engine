#pragma once
#include <DxLib.h>
#include <string>
#include "point.h"
#include "vector.h"
#include "color.h"

namespace dx_engine {
	using uint = unsigned int;

	enum class blend {
		none		= DX_BLENDMODE_NOBLEND, //�Ȃɂ����Ȃ�
		alpha		= DX_BLENDMODE_ALPHA, //�A���t�@�u�����h
		add			= DX_BLENDMODE_ADD, //���Z����
		mul			= DX_BLENDMODE_MUL, //��Z����
		mul_alpha	= DX_BLENDMODE_MULA, //�A���t�@�t����Z����
		sub			= DX_BLENDMODE_SUB, //���Z����
		inv_src		= DX_BLENDMODE_INVSRC, //�\�[�X�̔��]
		inv_dest	= DX_BLENDMODE_INVDESTCOLOR, //�`���̔��]
		pma_alpha	= DX_BLENDMODE_PMA_ALPHA, //��Z�ς݃A���t�@�u�����h�̃A���t�@�u�����h
		pma_add		= DX_BLENDMODE_PMA_ADD, //��Z�ς݃A���t�@�u�����h�̉��Z����
		pma_sub		= DX_BLENDMODE_PMA_SUB, //��Z�ς݃A���t�@�u�����h�̌��Z����
		pma_inv_src	= DX_BLENDMODE_PMA_INVSRC, //��Z�ς݃A���t�@�u�����h�̔��]����
	};

	class string : public std::string {
	private:
		using std::string::string;
		point<float> _position, _center;
		color _color;
		blend _blend = blend::alpha;
		byte _blendparam = 255;

		const char* _fontname = "";
		uint _fontsize;
		int _fonthandle = 0;
	public:
		string& centered(const point<float>& center);
		string& colored(const color& color);
		string& blend(blend mode, int param);
		string& at(const point<float>& position);

		point<float> position() const;
		point<float> size() const;
		void draw();
	};

	namespace detail {
		class _system final{
		private:
			ULONGLONG delta_msec = 0;
			float _fps;
		public:
			bool update();
			float delta_sec() const;
			double delta_sec_d() const;
			float fps() const;
			~_system();
		};

		class _window final{
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
			virtual shape& centered(const point<float>& center);
			virtual shape& rotateed(float angle);
			virtual shape& colored(const color& color);
			virtual shape& blend(blend mode, int param);
			virtual shape& at(const point<float>& position);

			virtual point<float> position() const;

			virtual void move(const point<float>& value);

			virtual void draw() = 0;
		};
	}

	class rect : public detail::shape {
	private:
		point<float> _size;
	public:
		rect();
		rect(const point<float> size);

		point<float> size() const;
		void resize(const point<float>& size);

		void draw() override;
	};

	extern detail::_system system;
	extern detail::_window window;
}