#include <stdlib.h>
#include <float.h>
#include <fenv.h>
#include <math.h>
#include <seagrass.h>

#pragma STDC FENV_ACCESS ON

#ifdef TEST
#include <test/cmocka.h>
#endif

int seagrass_float_ptr_compare(const float *const a, const float *const b) {
    seagrass_required_true(a || b);
    if (!b) {
        return (-1);
    } else if (!a) {
        return 1;
    }
    return seagrass_float_compare(*a, *b);
}

int seagrass_float_compare(const float a, const float b) {
    bool result;
    seagrass_required_true(!seagrass_float_is_less_than(a, b, &result));
    if (result) {
        return (-1);
    }
    seagrass_required_true(!seagrass_float_is_greater_than(a, b, &result));
    if (result) {
        return 1;
    }
    return 0;
}

int seagrass_float_minimum(const float a, const float b, float *const out) {
    if (!out) {
        return SEAGRASS_FLOAT_ERROR_OUT_IS_NULL;
    }
    bool result;
    seagrass_required_true(!seagrass_float_is_less_than(a, b, &result));
    if (result) {
        *out = a;
    } else {
        *out = b;
    }
    return 0;
}

int seagrass_float_maximum(const float a, const float b, float *const out) {
    if (!out) {
        return SEAGRASS_FLOAT_ERROR_OUT_IS_NULL;
    }
    bool result;
    seagrass_required_true(!seagrass_float_is_greater_than(a, b, &result));
    if (result) {
        *out = a;
    } else {
        *out = b;
    }
    return 0;
}

int seagrass_float_add(const float a, const float b, float *const out) {
    if (!out) {
        return SEAGRASS_FLOAT_ERROR_OUT_IS_NULL;
    }
    const float c = a + b;
    if ((b && (c == a)) || (a && (c == b))) {
        return SEAGRASS_FLOAT_ERROR_RESULT_IS_UNCHANGED;
    }
    bool result;
    seagrass_required_true(!seagrass_float_is_equal(c - a, b, &result));
    if (!result) {
        return SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT;
    }
    *out = c;
    return 0;
}

int seagrass_float_subtract(const float a, const float b, float *const out) {
    if (!out) {
        return SEAGRASS_FLOAT_ERROR_OUT_IS_NULL;
    }
    const float c = a - b;
    if ((b && (c == a)) || (a && (c == -b))) {
        return SEAGRASS_FLOAT_ERROR_RESULT_IS_UNCHANGED;
    }
    bool result;
    seagrass_required_true(!seagrass_float_is_equal(c - a, -b, &result));
    if (!result) {
        return SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT;
    }
    *out = c;
    return 0;
}

int seagrass_float_multiply(const float a, const float b, float *const out) {
    if (!out) {
        return SEAGRASS_FLOAT_ERROR_OUT_IS_NULL;
    }
    bool result;
    float A, B;
    seagrass_required_true(!seagrass_float_maximum(a, b, &A));
    seagrass_required_true(!seagrass_float_minimum(a, b, &B));
    const float C = A * B;
    seagrass_required_true(!seagrass_float_is_equal(C, 0, &result));
    if (result) {
        *out = 0;
        return 0;
    }
    seagrass_required_true(!seagrass_float_is_equal(C / A, B, &result));
    if (!result) {
        return SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT;
    }
    *out = C;
    return 0;
}

int seagrass_float_divide(const float a, const float b, float *const out) {
    if (!out) {
        return SEAGRASS_FLOAT_ERROR_OUT_IS_NULL;
    }
    bool result;
    seagrass_required_true(!seagrass_float_is_equal(b, 0, &result));
    if (result) {
        return SEAGRASS_FLOAT_ERROR_DIVIDE_BY_ZERO;
    }
    const float c = a / b;
    seagrass_required_true(!seagrass_float_is_equal(a, c * b, &result));
    if (!result) {
        return SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT;
    }
    *out = c;
    return 0;
}

int seagrass_float_is_equal(const float a, const float b, bool *const out) {
    if (!out) {
        return SEAGRASS_FLOAT_ERROR_OUT_IS_NULL;
    }
    *out = fabsf(a - b) <= FLT_EPSILON;
    return 0;
}

int seagrass_float_is_greater_than(const float a, const float b,
                                   bool *const out) {
    if (!out) {
        return SEAGRASS_FLOAT_ERROR_OUT_IS_NULL;
    }
    *out = (a - b) >= FLT_EPSILON;
    return 0;
}

int seagrass_float_is_less_than(const float a, const float b,
                                bool *const out) {
    if (!out) {
        return SEAGRASS_FLOAT_ERROR_OUT_IS_NULL;
    }
    *out = (a - b) <= -FLT_EPSILON;
    return 0;
}

int seagrass_float_is_greater_or_equal(const float a, const float b,
                                       bool *const out) {
    if (!out) {
        return SEAGRASS_FLOAT_ERROR_OUT_IS_NULL;
    }
    bool result;
    seagrass_required_true(!seagrass_float_is_greater_than(a, b, &result));
    seagrass_required_true(result || !seagrass_float_is_equal(a, b, &result));
    *out = result;
    return 0;
}

int seagrass_float_is_less_or_equal(const float a, const float b,
                                    bool *const out) {
    if (!out) {
        return SEAGRASS_FLOAT_ERROR_OUT_IS_NULL;
    }
    bool result;
    seagrass_required_true(!seagrass_float_is_less_than(a, b, &result));
    seagrass_required_true(result || !seagrass_float_is_equal(a, b, &result));
    *out = result;
    return 0;
}

int seagrass_float_to_uintmax_t(const float a,
                                const enum seagrass_float_rounding_mode mode,
                                uintmax_t *const out) {
    if (!out) {
        return SEAGRASS_FLOAT_ERROR_OUT_IS_NULL;
    }
    bool result;
    seagrass_required_true(!seagrass_float_is_less_than(a, 0, &result));
    if (result) {
        return SEAGRASS_FLOAT_ERROR_FLOAT_VALUE_IS_NEGATIVE;
    }
    const int round = fegetround();
    switch (mode) {
        default: {
            return SEAGRASS_FLOAT_ERROR_ROUNDING_MODE_IS_INVALID;
        }
        case SEAGRASS_FLOAT_ROUNDING_MODE_NEAREST: {
            seagrass_required_true(!fesetround(FE_TONEAREST));
            break;
        }
        case SEAGRASS_FLOAT_ROUNDING_MODE_DOWNWARD: {
            seagrass_required_true(!fesetround(FE_DOWNWARD));
            break;
        }
        case SEAGRASS_FLOAT_ROUNDING_MODE_UPWARD: {
            seagrass_required_true(!fesetround(FE_UPWARD));
            break;
        }
        case SEAGRASS_FLOAT_ROUNDING_MODE_TOWARDS_ZERO: {
            seagrass_required_true(!fesetround(FE_TOWARDZERO));
            break;
        }
    }
    seagrass_required_true(!feclearexcept(FE_ALL_EXCEPT));
    *out = llrintf(a);
    const int except = fetestexcept(FE_INVALID | FE_DIVBYZERO
                                    | FE_OVERFLOW | FE_UNDERFLOW);
    if (except & FE_INVALID) {
        return SEAGRASS_FLOAT_ERROR_FLOAT_VALUE_TOO_LARGE;
    }
    seagrass_required_true(!except);
    seagrass_required_true(!fesetround(round));
    return 0;
}
