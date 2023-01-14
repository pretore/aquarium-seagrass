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

bool seagrass_uintmax_t_minimum(const uintmax_t a, const uintmax_t b,
                                uintmax_t *out) {
    if (!out) {
        seagrass_error = SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL;
        return false;
    }
    *out = a < b ? a : b;
    return true;
}

bool seagrass_uintmax_t_maximum(const uintmax_t a, const uintmax_t b,
                                uintmax_t *out) {
    if (!out) {
        seagrass_error = SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL;
        return false;
    }
    *out = a > b ? a : b;
    return true;
}

bool seagrass_uintmax_t_add(const uintmax_t a, const uintmax_t b,
                            uintmax_t *out) {
    if (!out) {
        seagrass_error = SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL;
        return false;
    }
    const uintmax_t c = a + b;
    if (c < a) {
        seagrass_error = SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT;
        return false;
    }
    *out = c;
    return true;
}

bool seagrass_uintmax_t_subtract(const uintmax_t a, const uintmax_t b,
                                 uintmax_t *out) {
    if (!out) {
        seagrass_error = SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL;
        return false;
    }
    if (a < b) {
        seagrass_error = SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT;
        return false;
    }
    *out = a - b;
    return true;
}

bool seagrass_uintmax_t_multiply(const uintmax_t a, const uintmax_t b,
                                 uintmax_t *out) {
    if (!out) {
        seagrass_error = SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL;
        return false;
    }
    if (!a || !b) {
        *out = 0;
        return true;
    }
    const uintmax_t c = a * b;
    if (c / a != b) {
        seagrass_error = SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT;
        return false;
    }
    *out = c;
    return true;
}

bool seagrass_uintmax_t_divide(const uintmax_t a, const uintmax_t b,
                               uintmax_t *quotient, uintmax_t *remainder) {
    if (!quotient) {
        seagrass_error = SEAGRASS_UINTMAX_T_ERROR_QUOTIENT_IS_NULL;
        return false;
    }
    if (!b) {
        seagrass_error = SEAGRASS_UINTMAX_T_ERROR_DIVIDE_BY_ZERO;
        return false;
    }
    *quotient = a / b;
    if (remainder) {
        *remainder = a % b;
    }
    return true;
}

bool seagrass_uintmax_t_times_and_a_half_even(const uintmax_t current,
                                              uintmax_t *out) {
    if (!out) {
        seagrass_error = SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL;
        return false;
    }
    /* increase capacity by times and a half and then use the next even
     * number */
    size_t i = current >> 1;
    /* even numbers */
    if ((current & 1) ^ (i & 1)) {
        i += 1;
    }
    if (!seagrass_uintmax_t_add(current, i, out)) {
        seagrass_required_true(SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT
                               == seagrass_error);
        *out = UINTMAX_MAX;
    } else if (!current) {
        *out = 2;
    }
    return true;
}
