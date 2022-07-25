#include <stdlib.h>
#include <seagrass.h>

int seagrass_size_t_ptr_compare(const size_t *a, const size_t *b) {
    seagrass_required_true(a || b);
    if (!b) {
        return (-1);
    } else if (!a) {
        return 1;
    }
    return seagrass_size_t_compare(*a, *b);
}

int seagrass_size_t_compare(const size_t a, const size_t b) {
    return seagrass_void_ptr_compare((const void *) a, (const void *) b);
}

bool seagrass_size_t_minimum(const size_t a, const size_t b, size_t *out) {
    if (!out) {
        seagrass_error = SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL;
        return false;
    }
    *out = a < b ? a : b;
    return true;
}

bool seagrass_size_t_maximum(const size_t a, const size_t b, size_t *out) {
    if (!out) {
        seagrass_error = SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL;
        return false;
    }
    *out = a > b ? a : b;
    return true;
}

bool seagrass_size_t_add(const size_t a, const size_t b, size_t *out) {
    if (!out) {
        seagrass_error = SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL;
        return false;
    }
    const size_t c = a + b;
    if (c < a) {
        seagrass_error = SEAGRASS_SIZE_T_ERROR_RESULT_IS_INCONSISTENT;
        return false;
    }
    *out = c;
    return true;
}

bool seagrass_size_t_subtract(const size_t a, const size_t b, size_t *out) {
    if (!out) {
        seagrass_error = SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL;
        return false;
    }
    if (a < b) {
        seagrass_error = SEAGRASS_SIZE_T_ERROR_RESULT_IS_INCONSISTENT;
        return false;
    }
    *out = a - b;
    return true;
}

bool seagrass_size_t_multiply(const size_t a, const size_t b, size_t *out) {
    if (!out) {
        seagrass_error = SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL;
        return false;
    }
    if (!a || !b) {
        *out = 0;
        return true;
    }
    const size_t c = a * b;
    if (c / a != b) {
        seagrass_error = SEAGRASS_SIZE_T_ERROR_RESULT_IS_INCONSISTENT;
        return false;
    }
    *out = c;
    return true;
}

bool seagrass_size_t_divide(const size_t a, const size_t b, size_t *quotient,
                            size_t *remainder) {
    if (!quotient) {
        seagrass_error = SEAGRASS_SIZE_T_ERROR_QUOTIENT_IS_NULL;
        return false;
    }
    if (!b) {
        seagrass_error = SEAGRASS_SIZE_T_ERROR_DIVIDE_BY_ZERO;
        return false;
    }
    *quotient = a / b;
    if (remainder) {
        *remainder = a % b;
    }
    return true;
}

bool seagrass_size_t_times_and_a_half_even(const size_t current,
                                           size_t *out) {
    if (!out) {
        seagrass_error = SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL;
        return false;
    }
    /* increase capacity by times and a half and then use the next even
     * number */
    size_t i = current >> 1;
    /* even numbers */
    if ((current & 1) ^ (i & 1)) {
        i += 1;
    }
    if (!seagrass_size_t_add(current, i, out)) {
        seagrass_required_true(SEAGRASS_SIZE_T_ERROR_RESULT_IS_INCONSISTENT
                               == seagrass_error);
        *out = SIZE_MAX;
    } else if (!current) {
        *out = 2;
    }
    return true;
}
