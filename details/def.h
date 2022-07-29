#pragma once
#include <numbers>

#ifndef SCAST
#define SCAST(t, v) static_cast<t>((v))
#endif

#ifndef define
#define define constexpr auto
#endif

namespace dx_engine {
	using uint = unsigned int;
	using ulong = unsigned long;

	define PI = std::numbers::pi;
	define PI_F = std::numbers::pi_v<float>;
	define PI_2 = std::numbers::pi * 2.0;
	define PI_2F = std::numbers::pi_v<float> *2.0f;


	define YOCTO = 1e-24;
	define YOCTO_F = (float)YOCTO;

	define ZEPTO = 1e-21;
	define ZEPTO_F = (float)ZEPTO;

	define ATTO = 1e-18;
	define ATTO_F = (float)ATTO;

	define FEMTO = 1e-15;
	define FEMTO_F = (float)FEMTO;

	define PICO = 1e-12;
	define PICO_F = (float)PICO;

	define NANO = 1e-9;
	define NANO_F = (float)NANO;

	define MICRO = 1e-6;
	define MICRO_F = (float)MICRO;

	define MILLI = 1e-3;
	define MILLI_F = (float)MILLI;

	define CENTI = 1e-2;
	define CENTI_F = (float)CENTI;

	define DECI = 1e-1;
	define DECI_F = (float)DECI;

	define DECA = 1e1;
	define DECA_F = (float)DECA;
	define DECA_UL = (ulong)DECA;

	define HECTO = 1e2;
	define HECTO_F = (float)HECTO;
	define HECTO_UL = (ulong)HECTO;

	define KILO = 1e3;
	define KILO_F = (float)KILO;
	define KILO_UL = (ulong)KILO;

	define MEGA = 1e6;
	define MEGA_F = (float)MEGA;
	define MEGA_UL = (ulong)MEGA;

	define GIGA = 1e9;
	define GIGA_F = (float)GIGA;
	define GIGA_UL = (ulong)GIGA;

	define TERA = 1e12;
	define TERA_F = (float)TERA;

	define PETA = 1e15;
	define PETA_F = (float)PETA;

	define EXA = 1e18;
	define EXA_F = (float)EXA;

	define ZETTA = 1e21;
	define ZETTA_F = (float)ZETTA;

	define YOTTA = 1e24;
	define YOTTA_F = (float)YOTTA;


	define ENGINE = 0x00104;


}