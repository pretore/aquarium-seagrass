#include <stdlib.h>
#include <seagrass.h>

#ifdef TEST
#include <test/cmocka.h>
#endif

int seagrass_uintmax_t_ptr_compare(const uintmax_t *a, const uintmax_t *b) {
    seagrass_required_true(a || b);
    if (!b) {
        return (-1);
    } else if (!a) {
        return 1;
    }
    return seagrass_uintmax_t_compare(*a, *b);
}

int seagrass_uintmax_t_compare(const uintmax_t a, const uintmax_t b) {
    if (a == b) {
        return 0;
    } else if (a > b) {
        return 1;
    }
    return (-1);
}

int seagrass_uintmax_t_minimum(const uintmax_t a, const uintmax_t b,
                               uintmax_t *const out) {
    if (!out) {
        return SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL;
    }
    *out = a < b ? a : b;
    return 0;
}

int seagrass_uintmax_t_maximum(const uintmax_t a, const uintmax_t b,
                               uintmax_t *const out) {
    if (!out) {
        return SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL;
    }
    *out = a > b ? a : b;
    return 0;
}

int seagrass_uintmax_t_add(const uintmax_t a, const uintmax_t b,
                           uintmax_t *const out) {
    if (!out) {
        return SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL;
    }
    const uintmax_t c = a + b;
    if (c < a) {
        return SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT;
    }
    *out = c;
    return 0;
}

int seagrass_uintmax_t_subtract(const uintmax_t a, const uintmax_t b,
                                uintmax_t *const out) {
    if (!out) {
        return SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL;
    }
    if (a < b) {
        return SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT;
    }
    *out = a - b;
    return 0;
}

int seagrass_uintmax_t_multiply(const uintmax_t a, const uintmax_t b,
                                uintmax_t *const out) {
    if (!out) {
        return SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL;
    }
    if (!a || !b) {
        *out = 0;
        return 0;
    }
    const uintmax_t c = a * b;
    if (c / a != b) {
        return SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT;
    }
    *out = c;
    return 0;
}

int seagrass_uintmax_t_divide(const uintmax_t a, const uintmax_t b,
                              uintmax_t *const quotient,
                              uintmax_t *const remainder) {
    if (!quotient) {
        return SEAGRASS_UINTMAX_T_ERROR_QUOTIENT_IS_NULL;
    }
    if (!b) {
        return SEAGRASS_UINTMAX_T_ERROR_DIVIDE_BY_ZERO;
    }
    *quotient = a / b;
    if (remainder) {
        *remainder = a % b;
    }
    return 0;
}

int seagrass_uintmax_t_times_and_a_half_even(const uintmax_t current,
                                             uintmax_t *const out) {
    if (!out) {
        return SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL;
    }
    /* increase capacity by times and a half and then use the next even
     * number */
    uintmax_t i = current >> 1;
    /* even numbers */
    if ((current & 1) ^ (i & 1)) {
        i += 1;
    }
    int error;
    if ((error = seagrass_uintmax_t_add(current, i, out))) {
        seagrass_required_true(SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                               == error);
        *out = UINTMAX_MAX;
    } else if (!current) {
        *out = 2;
    }
    return true;
}
