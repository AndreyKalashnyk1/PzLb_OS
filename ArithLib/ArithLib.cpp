#include <climits>
#include "ArithLib.h"

ARITHAPI int Add64(int64_t a, int64_t b, int64_t* result)
{
    if (b > 0 && a > INT64_MAX - b) return ARITH_OVERFLOW;
    if (b < 0 && a < INT64_MIN - b) return ARITH_OVERFLOW;
    *result = a + b;
    return ARITH_OK;
}

ARITHAPI int Sub64(int64_t a, int64_t b, int64_t* result)
{
    if (b < 0 && a > INT64_MAX + b) return ARITH_OVERFLOW;
    if (b > 0 && a < INT64_MIN + b) return ARITH_OVERFLOW;
    *result = a - b;
    return ARITH_OK;
}

ARITHAPI int Mul64(int64_t a, int64_t b, int64_t* result)
{
    if (a != 0 && b != 0)
    {
        if (a > 0 && b > 0 && a > INT64_MAX / b) return ARITH_OVERFLOW;
        if (a < 0 && b < 0 && a < INT64_MAX / b) return ARITH_OVERFLOW;
        if (a > 0 && b < 0 && b < INT64_MIN / a) return ARITH_OVERFLOW;
        if (a < 0 && b > 0 && a < INT64_MIN / b) return ARITH_OVERFLOW;
    }
    *result = a * b;
    return ARITH_OK;
}

ARITHAPI int Div64(int64_t a, int64_t b, int64_t* result)
{
    if (b == 0)                    return ARITH_DIV_ZERO;
    if (a == INT64_MIN && b == -1) return ARITH_OVERFLOW;
    *result = a / b;
    return ARITH_OK;
}