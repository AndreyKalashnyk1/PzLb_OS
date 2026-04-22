#pragma once
#include <cstdint>

#ifdef ARITHLIB_EXPORTS
#   define ARITHAPI  extern "C" __declspec(dllexport)
#else
#   define ARITHAPI  extern "C" __declspec(dllimport)
#endif

#define ARITH_OK        0
#define ARITH_OVERFLOW  1
#define ARITH_DIV_ZERO  2

ARITHAPI int Add64(int64_t a, int64_t b, int64_t* result);
ARITHAPI int Sub64(int64_t a, int64_t b, int64_t* result);
ARITHAPI int Mul64(int64_t a, int64_t b, int64_t* result);
ARITHAPI int Div64(int64_t a, int64_t b, int64_t* result);