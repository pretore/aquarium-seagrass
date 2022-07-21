#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <seagrass.h>
#include <float.h>

#include "test/cmocka.h"
#include "test/wrap.h"

static void check_float_ptr_compare(void **state) {
    const float q[] = {
            0,
            1
    };
    const float* i[] = {
            &q[0],
            &q[1]
    };
    assert_int_equal((-1), seagrass_float_ptr_compare(i[0], i[1]));
    assert_int_equal((-1), seagrass_float_ptr_compare(i[1], NULL));
    assert_int_equal((-1), seagrass_float_ptr_compare(i[0], NULL));
    assert_int_equal(0, seagrass_float_ptr_compare(i[0], i[0]));
    assert_int_equal(0, seagrass_float_ptr_compare(i[1], i[1]));
    assert_int_equal(1, seagrass_float_ptr_compare(i[1], i[0]));
    assert_int_equal(1, seagrass_float_ptr_compare(NULL, i[0]));
    assert_int_equal(1, seagrass_float_ptr_compare(NULL, i[1]));

    abort_is_overridden = true;
    expect_function_call(__wrap_abort);
    seagrass_float_ptr_compare(NULL, NULL);
    abort_is_overridden = false;
}

static void check_float_compare(void **state) {
    const float i[] = {
            0,
            1
    };
    assert_int_equal((-1), seagrass_float_compare(i[0], i[1]));
    assert_int_equal(0, seagrass_float_compare(i[0], i[0]));
    assert_int_equal(0, seagrass_float_compare(i[1], i[1]));
    assert_int_equal(1, seagrass_float_compare(i[1], i[0]));
}

static void check_float_minimum_error_on_out_is_null(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_float_minimum(0, 1, NULL));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_OUT_IS_NULL, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_minimum(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    float result;
    assert_true(seagrass_float_minimum(-FLT_EPSILON, 0, &result));
    assert_float_equal(result, -FLT_EPSILON, FLT_EPSILON);
    assert_true(seagrass_float_minimum(0, -FLT_EPSILON, &result));
    assert_float_equal(result, -FLT_EPSILON, FLT_EPSILON);
    assert_true(seagrass_float_minimum(FLT_MAX, 0, &result));
    assert_float_equal(result, 0, FLT_EPSILON);
    assert_true(seagrass_float_minimum(0, FLT_MAX, &result));
    assert_float_equal(result, 0, FLT_EPSILON);
    assert_true(seagrass_float_minimum(-FLT_MAX, 0, &result));
    assert_float_equal(result, -FLT_MAX, FLT_EPSILON);
    assert_true(seagrass_float_minimum(0, -FLT_MAX, &result));
    assert_float_equal(result, -FLT_MAX, FLT_EPSILON);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_maximum_error_on_out_is_null(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_float_maximum(0, 1, NULL));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_OUT_IS_NULL, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_maximum(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    float result;
    assert_true(seagrass_float_maximum(FLT_EPSILON, 0, &result));
    assert_float_equal(result, FLT_EPSILON, FLT_EPSILON);
    assert_true(seagrass_float_maximum(0, FLT_EPSILON, &result));
    assert_float_equal(result, FLT_EPSILON, FLT_EPSILON);
    assert_true(seagrass_float_maximum(FLT_MAX, 0, &result));
    assert_float_equal(result, FLT_MAX, FLT_EPSILON);
    assert_true(seagrass_float_maximum(0, FLT_MAX, &result));
    assert_float_equal(result, FLT_MAX, FLT_EPSILON);
    assert_true(seagrass_float_maximum(-FLT_MAX, 0, &result));
    assert_float_equal(result, 0, FLT_EPSILON);
    assert_true(seagrass_float_maximum(0, -FLT_MAX, &result));
    assert_float_equal(result, 0, FLT_EPSILON);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_add_error_on_out_is_null(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_float_add(0, 0, NULL));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_OUT_IS_NULL, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_add_error_on_result_is_inconsistent(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    float result;
    assert_false(seagrass_float_add( FLT_MAX, 1, &result));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT, seagrass_error);
    assert_false(seagrass_float_add(1, FLT_MAX, &result));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_add(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    float result;
    assert_true(seagrass_float_add(1, 1, &result));
    assert_float_equal(result, 2, FLT_EPSILON);
    assert_true(seagrass_float_add(100000, 100000, &result));
    assert_float_equal(result, 200000, FLT_EPSILON);
    assert_true(seagrass_float_add(1000000000, 1000000000, &result));
    assert_float_equal(result, 2000000000, FLT_EPSILON);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_multiply_error_on_out_is_null(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_float_multiply(0, 1, NULL));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_OUT_IS_NULL, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_multiply_error_on_result_is_inconsistent(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    float result;
    assert_false(seagrass_float_multiply(2, FLT_MAX, &result));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT,
                     seagrass_error);
    assert_false(seagrass_float_multiply(FLT_MAX, 2, &result));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT,
                     seagrass_error);
    assert_false(seagrass_float_multiply(2, -FLT_MAX, &result));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT,
                     seagrass_error);
    assert_false(seagrass_float_multiply(-FLT_MAX, 2, &result));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT,
                     seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_multiply(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    float result;
    assert_true(seagrass_float_multiply(2, 2, &result));
    assert_float_equal(4, result, FLT_EPSILON);
    assert_true(seagrass_float_multiply(20000, 20000, &result));
    assert_float_equal(400000000, result, FLT_EPSILON);
    assert_true(seagrass_float_multiply(20000, -20000, &result));
    assert_float_equal(-400000000, result, FLT_EPSILON);
    assert_true(seagrass_float_multiply(400000000, 0, &result));
    assert_float_equal(0, result, FLT_EPSILON);
    assert_true(seagrass_float_multiply(0, 400000000, &result));
    assert_float_equal(0, result, FLT_EPSILON);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_is_equal_error_on_out_is_null(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_float_is_equal(0, 0, NULL));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_OUT_IS_NULL, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_is_equal(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    bool result;
    assert_true(seagrass_float_is_equal(1.0, 1.0, &result));
    assert_true(result);
    assert_true(seagrass_float_is_equal(1.1, 1.0, &result));
    assert_false(result);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_is_greater_than_error_on_out_is_null(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_float_is_greater_than(0, 1.2, NULL));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_OUT_IS_NULL, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_is_greater_than(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    bool result;
    assert_true(seagrass_float_is_greater_than(0.12, 1.0, &result));
    assert_false(result);
    assert_true(seagrass_float_is_greater_than(1.0, 0.12, &result));
    assert_true(result);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_is_less_than_error_on_out_is_null(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_float_is_less_than(1.0, 0, NULL));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_OUT_IS_NULL, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_is_less_than(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    bool result;
    assert_true(seagrass_float_is_less_than(2.1, 1.2, &result));
    assert_false(result);
    assert_true(seagrass_float_is_less_than(1.1, 1.2, &result));
    assert_true(result);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_is_greater_or_equal_error_on_out_is_null(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_float_is_greater_or_equal(1.0, 0, NULL));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_OUT_IS_NULL, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_is_greater_or_equal(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    bool result;
    assert_true(seagrass_float_is_greater_or_equal(1.1, 1.0, &result));
    assert_true(result);
    assert_true(seagrass_float_is_greater_or_equal(1.0, 1.0, &result));
    assert_true(result);
    assert_true(seagrass_float_is_greater_or_equal(0.9, 1.0, &result));
    assert_false(result);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void
check_float_is_less_than_or_equal_error_on_out_is_null(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_float_is_greater_or_equal(1.0, 1.1, NULL));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_OUT_IS_NULL, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_is_less_than_or_equal(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    bool result;
    assert_true(seagrass_float_is_less_or_equal(1.1, 2.1, &result));
    assert_true(result);
    assert_true(seagrass_float_is_less_or_equal(1.1, 1.1, &result));
    assert_true(result);
    assert_true(seagrass_float_is_less_or_equal(1.0, 0.9, &result));
    assert_false(result);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_to_size_t_error_on_out_is_null(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_float_to_size_t(0, 0, NULL));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_OUT_IS_NULL, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_to_size_t_error_on_mode_is_invalid(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_float_to_size_t(0, SIZE_MAX, (void *)1));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_MODE_IS_INVALID, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void
check_float_to_size_t_error_on_float_value_is_negative(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    size_t result;
    assert_false(seagrass_float_to_size_t(
            -FLT_EPSILON,
            SEAGRASS_FLOAT_ROUNDING_MODE_TOWARDS_ZERO,
            &result));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_FLOAT_VALUE_IS_NEGATIVE,
                     seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_to_size_t_error_on_float_value_too_large(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    size_t result;
    assert_false(seagrass_float_to_size_t(
            FLT_MAX,
            SEAGRASS_FLOAT_ROUNDING_MODE_NEAREST,
            &result));
    assert_int_equal(SEAGRASS_FLOAT_ERROR_FLOAT_VALUE_TOO_LARGE, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_to_size_t_with_round_mode_nearest(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    size_t result;
    assert_true(seagrass_float_to_size_t(
            6.2,
            SEAGRASS_FLOAT_ROUNDING_MODE_NEAREST,
            &result));
    assert_int_equal(6, result);
    assert_true(seagrass_float_to_size_t(
            18.7,
            SEAGRASS_FLOAT_ROUNDING_MODE_NEAREST,
            &result));
    assert_int_equal(19, result);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_to_size_t_with_round_mode_downward(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    size_t result;
    assert_true(seagrass_float_to_size_t(
            6.2,
            SEAGRASS_FLOAT_ROUNDING_MODE_DOWNWARD,
            &result));
    assert_int_equal(6, result);
    assert_true(seagrass_float_to_size_t(
            19.7,
            SEAGRASS_FLOAT_ROUNDING_MODE_DOWNWARD,
            &result));
    assert_int_equal(19, result);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_to_size_t_with_round_mode_upward(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    size_t result;
    assert_true(seagrass_float_to_size_t(
            6.2,
            SEAGRASS_FLOAT_ROUNDING_MODE_UPWARD,
            &result));
    assert_int_equal(7, result);
    assert_true(seagrass_float_to_size_t(
            19.7,
            SEAGRASS_FLOAT_ROUNDING_MODE_UPWARD,
            &result));
    assert_int_equal(20, result);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_float_to_size_t_with_round_mode_towards_zero(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    size_t result;
    assert_true(seagrass_float_to_size_t(
            6.2,
            SEAGRASS_FLOAT_ROUNDING_MODE_TOWARDS_ZERO,
            &result));
    assert_int_equal(6, result);
    assert_true(seagrass_float_to_size_t(
            19.7,
            SEAGRASS_FLOAT_ROUNDING_MODE_TOWARDS_ZERO,
            &result));
    assert_int_equal(19, result);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

int main(int argc, char *argv[]) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(check_float_ptr_compare),
            cmocka_unit_test(check_float_compare),
            cmocka_unit_test(check_float_minimum_error_on_out_is_null),
            cmocka_unit_test(check_float_minimum),
            cmocka_unit_test(check_float_maximum_error_on_out_is_null),
            cmocka_unit_test(check_float_maximum),
            cmocka_unit_test(check_float_add_error_on_out_is_null),
            cmocka_unit_test(check_float_add_error_on_result_is_inconsistent),
            cmocka_unit_test(check_float_add),
            cmocka_unit_test(check_float_multiply_error_on_out_is_null),
            cmocka_unit_test(check_float_multiply_error_on_result_is_inconsistent),
            cmocka_unit_test(check_float_multiply),
            cmocka_unit_test(check_float_is_equal_error_on_out_is_null),
            cmocka_unit_test(check_float_is_equal),
            cmocka_unit_test(check_float_is_greater_than_error_on_out_is_null),
            cmocka_unit_test(check_float_is_greater_than),
            cmocka_unit_test(check_float_is_less_than_error_on_out_is_null),
            cmocka_unit_test(check_float_is_less_than),
            cmocka_unit_test(check_float_is_greater_or_equal_error_on_out_is_null),
            cmocka_unit_test(check_float_is_greater_or_equal),
            cmocka_unit_test(check_float_is_less_than_or_equal_error_on_out_is_null),
            cmocka_unit_test(check_float_is_less_than_or_equal),
            cmocka_unit_test(check_float_to_size_t_error_on_out_is_null),
            cmocka_unit_test(check_float_to_size_t_error_on_mode_is_invalid),
            cmocka_unit_test(check_float_to_size_t_error_on_float_value_is_negative),
            cmocka_unit_test(check_float_to_size_t_error_on_float_value_too_large),
            cmocka_unit_test(check_float_to_size_t_with_round_mode_nearest),
            cmocka_unit_test(check_float_to_size_t_with_round_mode_downward),
            cmocka_unit_test(check_float_to_size_t_with_round_mode_upward),
            cmocka_unit_test(check_float_to_size_t_with_round_mode_towards_zero),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
