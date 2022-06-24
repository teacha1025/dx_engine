#pragma once
#include <string>
#include <format>
#include <vector>
#include <DxLib.h>

#include "point.h"
#include "vector.h"
#include "color.h"
#include "pallet.h"
#include "device.h"

namespace dx_engine {
	using uint = unsigned int;

	enum class blend {
		none		= DX_BLENDMODE_NOBLEND, //なにもしない
		alpha		= DX_BLENDMODE_ALPHA, //アルファブレンド
		add			= DX_BLENDMODE_ADD, //加算合成
		mul			= DX_BLENDMODE_MUL, //乗算合成
		mul_alpha	= DX_BLENDMODE_MULA, //アルファ付き乗算合成
		sub			= DX_BLENDMODE_SUB, //減算合成
		inv_src		= DX_BLENDMODE_INVSRC, //ソースの反転
		inv_dest	= DX_BLENDMODE_INVDESTCOLOR, //描画先の反転
		pma_alpha	= DX_BLENDMODE_PMA_ALPHA, //乗算済みアルファブレンドのアルファブレンド
		pma_add		= DX_BLENDMODE_PMA_ADD, //乗算済みアルファブレンドの加算合成
		pma_sub		= DX_BLENDMODE_PMA_SUB, //乗算済みアルファブレンドの減算合成
		pma_inv_src	= DX_BLENDMODE_PMA_INVSRC, //乗算済みアルファブレンドの反転合成
	};

	enum class font_type {
		normal = DX_FONTTYPE_NORMAL,
		edge = DX_FONTTYPE_EDGE,
		anti_aliasing = DX_FONTTYPE_ANTIALIASING,
		edged_anti_aliasing = DX_FONTTYPE_ANTIALIASING_EDGE
	};



	class string {
	private:
		std::string _str;
		point<float> _position = {0,0}, _center = {0,0};
		color _color = pallet::black, _edgecolor = pallet::black;
		blend _blend = blend::alpha;
		byte _blendparam = 255;

		int _fonthandle = 0;
	public:
		string() = default;
		string(const string&) = default;
		string(const std::string& str);
		string(const char* str);
		string& centered(const dx_engine::point<float>& center);
		string& colored(const dx_engine::color& color, const dx_engine::color& edge = pallet::black);
		string& blend(dx_engine::blend mode, int param);
		string& at(const dx_engine::point<float>& position);

		point<float> position() const;
		point<float> size() const;

		std::string& get();

		void set_font(const std::string& fontname = "", dx_engine::uint size = 16, dx_engine::uint thick = 1, dx_engine::font_type type = font_type::normal, uint edgesize = -1, bool italic = false);
		void draw();
	};

	namespace detail {
		class _system final{
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

		class _window final{
		private:
			point<dx_engine::uint> _size = {1280, 960};
		public:
			void size(const dx_engine::point<dx_engine::uint>& size);
			point<dx_engine::uint> size() const;
		};

		class shape {
		protected:
			point<float> _position, _center;
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

	class texture {
	private:
		point<float> _size, _position, _center;
		blend _blend = blend::alpha;
		byte _blendparam = 255;

		int _handle = 0;
		std::vector<int> _div_handle;
		bool _isdiv = false;
		bool _isturn = false;
		bool _isflip = false;
		double _angle = 0.0, _rate = 1.0;
		point<int> _div_num = { 1,1 };
		int _draw_mode = DX_DRAWMODE_NEAREST;
	public:
		texture();
		texture(const point<int>& size, const color& fill_color = pallet::white);
		texture(const int& handle);
		texture(const std::string& path);
		texture(const std::string& path, const point<int>& divnum);

		texture& centered(const dx_engine::point<float>& center);
		texture& rotateed(float angle);
		texture& blend(dx_engine::blend mode, int param);
		texture& at(const dx_engine::point<float>& position);
		texture& extended(float rate);
		texture& turned(bool flag);
		texture& fliped(bool flag);

		point<float> position() const;

		void draw();

		texture operator [](const uint& i)const;
	};

	extern detail::_system system;
	extern detail::_window window;
}