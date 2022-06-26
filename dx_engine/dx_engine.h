#pragma once
#include "heads.h"

#ifdef _DEBUG
#ifdef _M_X64
#pragma comment(lib, "dx_engine_d_64")
#else
#pragma comment(lib, "dx_engine_d")
#endif
#else
#ifdef _M_X64
#pragma comment(lib, "dx_engine_64")
#else
#pragma comment(lib, "dx_engine")
#endif
#endif

#ifdef SCAST
#undef SCAST
#endif 