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

bool seagrass_size_t_add(const size_t a, const size_t b, size_t *out) {
    if (!out) {
        seagrass_error = SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL;
        return false;
    }
    const size_t result = a + b;
    if (result < a) {
        seagrass_error = SEAGRASS_SIZE_T_ERROR_RESULT_IS_INCONSISTENT;
        return false;
    }
    *out = result;
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
    const size_t result = a * b;
    if (result / a != b) {
        seagrass_error = SEAGRASS_SIZE_T_ERROR_RESULT_IS_INCONSISTENT;
        return false;
    }
    *out = result;
    return true;
}
