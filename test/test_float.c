#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <float.h>
#include <seagrass.h>

#include <test/cmocka.h>

static void check_float_ptr_compare(void **state) {
    const float q[] = {
            0,
            1
    };
    const float *i[] = {
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
    expect_function_call(cmocka_test_abort);
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
    assert_int_equal(
            seagrass_float_minimum(0, 1, NULL),
            SEAGRASS_FLOAT_ERROR_OUT_IS_NULL);
}

static void check_float_minimum(void **state) {
    float result;
    assert_int_equal(
            seagrass_float_minimum(-FLT_EPSILON, 0, &result), 0);
    assert_float_equal(result, -FLT_EPSILON, FLT_EPSILON);
    assert_int_equal(
            seagrass_float_minimum(0, -FLT_EPSILON, &result), 0);
    assert_float_equal(result, -FLT_EPSILON, FLT_EPSILON);
    assert_int_equal(
            seagrass_float_minimum(FLT_MAX, 0, &result), 0);
    assert_float_equal(result, 0, FLT_EPSILON);
    assert_int_equal(
            seagrass_float_minimum(0, FLT_MAX, &result), 0);
    assert_float_equal(result, 0, FLT_EPSILON);
    assert_int_equal(
            seagrass_float_minimum(-FLT_MAX, 0, &result), 0);
    assert_float_equal(result, -FLT_MAX, FLT_EPSILON);
    assert_int_equal(
            seagrass_float_minimum(0, -FLT_MAX, &result), 0);
    assert_float_equal(result, -FLT_MAX, FLT_EPSILON);
}

static void check_float_maximum_error_on_out_is_null(void **state) {
    assert_int_equal(
            seagrass_float_maximum(0, 1, NULL),
            SEAGRASS_FLOAT_ERROR_OUT_IS_NULL);
}

static void check_float_maximum(void **state) {
    float result;
    assert_int_equal(
            seagrass_float_maximum(FLT_EPSILON, 0, &result), 0);
    assert_float_equal(result, FLT_EPSILON, FLT_EPSILON);
    assert_int_equal(
            seagrass_float_maximum(0, FLT_EPSILON, &result), 0);
    assert_float_equal(result, FLT_EPSILON, FLT_EPSILON);
    assert_int_equal(
            seagrass_float_maximum(FLT_MAX, 0, &result), 0);
    assert_float_equal(result, FLT_MAX, FLT_EPSILON);
    assert_int_equal(
            seagrass_float_maximum(0, FLT_MAX, &result), 0);
    assert_float_equal(result, FLT_MAX, FLT_EPSILON);
    assert_int_equal(
            seagrass_float_maximum(-FLT_MAX, 0, &result), 0);
    assert_float_equal(result, 0, FLT_EPSILON);
    assert_int_equal(
            seagrass_float_maximum(0, -FLT_MAX, &result), 0);
    assert_float_equal(result, 0, FLT_EPSILON);
}

static void check_float_add_error_on_out_is_null(void **state) {
    assert_int_equal(
            seagrass_float_add(0, 0, NULL),
            SEAGRASS_FLOAT_ERROR_OUT_IS_NULL);
}

static void check_float_add_error_on_result_is_inconsistent(void **state) {
    float result;
    assert_int_equal(
            seagrass_float_add(FLT_MAX, FLT_MAX, &result),
            SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT);
    assert_int_equal(
            seagrass_float_add(-FLT_MAX, -FLT_MAX, &result),
            SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT);
}

static void check_float_add_error_on_result_is_unchanged(void **state) {
    float result;
    assert_int_equal(
            seagrass_float_add(FLT_MAX, 1, &result),
            SEAGRASS_FLOAT_ERROR_RESULT_IS_UNCHANGED);
    assert_int_equal(
            seagrass_float_add(1, FLT_MAX, &result),
            SEAGRASS_FLOAT_ERROR_RESULT_IS_UNCHANGED);
}

static void check_float_add(void **state) {
    float result;
    assert_int_equal(
            seagrass_float_add(1, 1, &result), 0);
    assert_float_equal(result, 2, FLT_EPSILON);
    assert_int_equal(
            seagrass_float_add(100000, 100000, &result), 0);
    assert_float_equal(result, 200000, FLT_EPSILON);
    assert_int_equal(
            seagrass_float_add(1000000000, 1000000000, &result), 0);
    assert_float_equal(result, 2000000000, FLT_EPSILON);
}

static void check_float_subtract_error_on_out_is_null(void **state) {
    assert_int_equal(
            seagrass_float_subtract(0, 0, NULL),
            SEAGRASS_FLOAT_ERROR_OUT_IS_NULL);
}

static void check_float_subtract_error_on_result_is_inconsistent(void **state) {
    float result;
    assert_int_equal(
            seagrass_float_subtract(FLT_MAX, -FLT_MAX, &result),
            SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT);
    assert_int_equal(
            seagrass_float_subtract(-FLT_MAX, FLT_MAX, &result),
            SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT);
}

static void check_float_subtract_error_on_result_is_unchanged(void **state) {
    float result;
    assert_int_equal(
            seagrass_float_subtract(-FLT_MAX, 1, &result),
            SEAGRASS_FLOAT_ERROR_RESULT_IS_UNCHANGED);
    assert_int_equal(
            seagrass_float_subtract(-1, FLT_MAX, &result),
            SEAGRASS_FLOAT_ERROR_RESULT_IS_UNCHANGED);
}

static void check_float_subtract(void **state) {
    float result;
    assert_int_equal(
            seagrass_float_subtract(1, 1, &result), 0);
    assert_float_equal(result, 0, FLT_EPSILON);
    assert_int_equal(
            seagrass_float_subtract(100000, 1000000, &result), 0);
    assert_float_equal(result, -900000, FLT_EPSILON);
    assert_int_equal(
            seagrass_float_subtract(1000000000, -1000000000, &result), 0);
    assert_float_equal(result, 2000000000, FLT_EPSILON);
}

static void check_float_multiply_error_on_out_is_null(void **state) {
    assert_int_equal(
            seagrass_float_multiply(0, 1, NULL),
            SEAGRASS_FLOAT_ERROR_OUT_IS_NULL);
}

static void check_float_multiply_error_on_result_is_inconsistent(void **state) {
    float result;
    assert_int_equal(
            seagrass_float_multiply(2, FLT_MAX, &result),
            SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT);
    assert_int_equal(
            seagrass_float_multiply(FLT_MAX, 2, &result),
            SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT);
    assert_int_equal(
            seagrass_float_multiply(2, -FLT_MAX, &result),
            SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT);
    assert_int_equal(
            seagrass_float_multiply(-FLT_MAX, 2, &result),
            SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT);
}

static void check_float_multiply(void **state) {
    float result;
    assert_int_equal(
            seagrass_float_multiply(2, 2, &result), 0);
    assert_float_equal(4, result, FLT_EPSILON);
    assert_int_equal(
            seagrass_float_multiply(20000, 20000, &result), 0);
    assert_float_equal(400000000, result, FLT_EPSILON);
    assert_int_equal(
            seagrass_float_multiply(20000, -20000, &result), 0);
    assert_float_equal(-400000000, result, FLT_EPSILON);
    assert_int_equal(
            seagrass_float_multiply(400000000, 0, &result), 0);
    assert_float_equal(0, result, FLT_EPSILON);
    assert_int_equal(
            seagrass_float_multiply(0, 400000000, &result), 0);
    assert_float_equal(0, result, FLT_EPSILON);
}

static void check_float_divide_error_on_out_is_null(void **state) {
    assert_int_equal(
            seagrass_float_divide(2, 1, NULL),
            SEAGRASS_FLOAT_ERROR_OUT_IS_NULL);
}

static void check_float_divide_error_on_divide_by_zero(void **state) {
    assert_int_equal(
            seagrass_float_divide(1, 0, (void *) 1),
            SEAGRASS_FLOAT_ERROR_DIVIDE_BY_ZERO);
}

static void check_float_divide_error_on_result_is_inconsistent(void **state) {
    float result;
    assert_int_equal(
            seagrass_float_divide(FLT_MAX, 0.00001, &result),
            SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT);
}

static void check_float_divide(void **state) {
    float result;
    assert_int_equal(seagrass_float_divide(1, -0.1, &result), 0);
    assert_float_equal(-10, result, FLT_EPSILON);
}

static void check_float_is_equal_error_on_out_is_null(void **state) {
    assert_int_equal(
            seagrass_float_is_equal(0, 0, NULL),
            SEAGRASS_FLOAT_ERROR_OUT_IS_NULL);
}

static void check_float_is_equal(void **state) {
    bool result;
    assert_int_equal(
            seagrass_float_is_equal(1.0, 1.0, &result), 0);
    assert_true(result);
    assert_int_equal(
            seagrass_float_is_equal(1.1, 1.0, &result), 0);
    assert_false(result);
}

static void check_float_is_greater_than_error_on_out_is_null(void **state) {
    assert_int_equal(
            seagrass_float_is_greater_than(0, 1.2, NULL),
            SEAGRASS_FLOAT_ERROR_OUT_IS_NULL);
}

static void check_float_is_greater_than(void **state) {
    bool result;
    assert_int_equal(
            seagrass_float_is_greater_than(0.12, 1.0, &result), 0);
    assert_false(result);
    assert_int_equal(
            seagrass_float_is_greater_than(1.0, 0.12, &result), 0);
    assert_true(result);
}

static void check_float_is_less_than_error_on_out_is_null(void **state) {
    assert_int_equal(
            seagrass_float_is_less_than(1.0, 0, NULL),
            SEAGRASS_FLOAT_ERROR_OUT_IS_NULL);
}

static void check_float_is_less_than(void **state) {
    bool result;
    assert_int_equal(
            seagrass_float_is_less_than(2.1, 1.2, &result), 0);
    assert_false(result);
    assert_int_equal(
            seagrass_float_is_less_than(1.1, 1.2, &result), 0);
    assert_true(result);
}

static void check_float_is_greater_or_equal_error_on_out_is_null(void **state) {
    assert_int_equal(
            seagrass_float_is_greater_or_equal(1.0, 0, NULL),
            SEAGRASS_FLOAT_ERROR_OUT_IS_NULL);
}

static void check_float_is_greater_or_equal(void **state) {
    bool result;
    assert_int_equal(
            seagrass_float_is_greater_or_equal(1.1, 1.0, &result), 0);
    assert_true(result);
    assert_int_equal(
            seagrass_float_is_greater_or_equal(1.0, 1.0, &result), 0);
    assert_true(result);
    assert_int_equal(
            seagrass_float_is_greater_or_equal(0.9, 1.0, &result), 0);
    assert_false(result);
}

static void
check_float_is_less_than_or_equal_error_on_out_is_null(void **state) {
    assert_int_equal(
            seagrass_float_is_greater_or_equal(1.0, 1.1, NULL),
            SEAGRASS_FLOAT_ERROR_OUT_IS_NULL);
}

static void check_float_is_less_than_or_equal(void **state) {
    bool result;
    assert_int_equal(
            seagrass_float_is_less_or_equal(1.1, 2.1, &result), 0);
    assert_true(result);
    assert_int_equal(
            seagrass_float_is_less_or_equal(1.1, 1.1, &result), 0);
    assert_true(result);
    assert_int_equal(
            seagrass_float_is_less_or_equal(1.0, 0.9, &result), 0);
    assert_false(result);
}

static void check_float_to_uintmax_t_error_on_out_is_null(void **state) {
    assert_int_equal(
            seagrass_float_to_uintmax_t(0, 0, NULL),
            SEAGRASS_FLOAT_ERROR_OUT_IS_NULL);
}

static void
check_float_to_uintmax_t_error_on_rounding_mode_is_invalid(void **state) {
    assert_int_equal(
            seagrass_float_to_uintmax_t(0, ~0, (void *) 1),
            SEAGRASS_FLOAT_ERROR_ROUNDING_MODE_IS_INVALID);
}

static void
check_float_to_uintmax_t_error_on_float_value_is_negative(void **state) {
    uintmax_t result;
    assert_int_equal(
            seagrass_float_to_uintmax_t(
                    -FLT_EPSILON,
                    SEAGRASS_FLOAT_ROUNDING_MODE_TOWARDS_ZERO,
                    &result),
                    SEAGRASS_FLOAT_ERROR_FLOAT_VALUE_IS_NEGATIVE);
}

static void
check_float_to_uintmax_t_error_on_float_value_too_large(void **state) {
    uintmax_t result;
    assert_int_equal(
            seagrass_float_to_uintmax_t(
                    FLT_MAX,
                    SEAGRASS_FLOAT_ROUNDING_MODE_NEAREST,
                    &result),
                    SEAGRASS_FLOAT_ERROR_FLOAT_VALUE_TOO_LARGE);
}

static void check_float_to_uintmax_t_with_rounding_mode_nearest(void **state) {
    uintmax_t result;
    assert_int_equal(
            seagrass_float_to_uintmax_t(
                    6.2,
                    SEAGRASS_FLOAT_ROUNDING_MODE_NEAREST,
                    &result), 0);
    assert_int_equal(6, result);
    assert_int_equal(
            seagrass_float_to_uintmax_t(
                    18.7,
                    SEAGRASS_FLOAT_ROUNDING_MODE_NEAREST,
                    &result), 0);
    assert_int_equal(19, result);
}

static void
check_float_to_uintmax_t_with_rounding_mode_downward(void **state) {
    uintmax_t result;
    assert_int_equal(
            seagrass_float_to_uintmax_t(
                    6.2,
                    SEAGRASS_FLOAT_ROUNDING_MODE_DOWNWARD,
                    &result), 0);
    assert_int_equal(6, result);
    assert_int_equal(
            seagrass_float_to_uintmax_t(
                    19.7,
                    SEAGRASS_FLOAT_ROUNDING_MODE_DOWNWARD,
                    &result), 0);
    assert_int_equal(19, result);
}

static void check_float_to_uintmax_t_with_rounding_mode_upward(void **state) {
    uintmax_t result;
    assert_int_equal(
            seagrass_float_to_uintmax_t(
                    6.2,
                    SEAGRASS_FLOAT_ROUNDING_MODE_UPWARD,
                    &result), 0);
    assert_int_equal(7, result);
    assert_int_equal(
            seagrass_float_to_uintmax_t(
                    19.7,
                    SEAGRASS_FLOAT_ROUNDING_MODE_UPWARD,
                    &result), 0);
    assert_int_equal(20, result);
}

static void
check_float_to_uintmax_t_with_rounding_mode_towards_zero(void **state) {
    uintmax_t result;
    assert_int_equal(
            seagrass_float_to_uintmax_t(
                    6.2,
                    SEAGRASS_FLOAT_ROUNDING_MODE_TOWARDS_ZERO,
                    &result), 0);
    assert_int_equal(6, result);
    assert_int_equal(
            seagrass_float_to_uintmax_t(
                    19.7,
                    SEAGRASS_FLOAT_ROUNDING_MODE_TOWARDS_ZERO,
                    &result), 0);
    assert_int_equal(19, result);
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
            cmocka_unit_test(check_float_add_error_on_result_is_unchanged),
            cmocka_unit_test(check_float_add),
            cmocka_unit_test(check_float_subtract_error_on_out_is_null),
            cmocka_unit_test(check_float_subtract_error_on_result_is_inconsistent),
            cmocka_unit_test(check_float_subtract_error_on_result_is_unchanged),
            cmocka_unit_test(check_float_subtract),
            cmocka_unit_test(check_float_multiply_error_on_out_is_null),
            cmocka_unit_test(check_float_multiply_error_on_result_is_inconsistent),
            cmocka_unit_test(check_float_multiply),
            cmocka_unit_test(check_float_divide_error_on_out_is_null),
            cmocka_unit_test(check_float_divide_error_on_divide_by_zero),
            cmocka_unit_test(check_float_divide_error_on_result_is_inconsistent),
            cmocka_unit_test(check_float_divide),
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
            cmocka_unit_test(check_float_to_uintmax_t_error_on_out_is_null),
            cmocka_unit_test(check_float_to_uintmax_t_error_on_rounding_mode_is_invalid),
            cmocka_unit_test(check_float_to_uintmax_t_error_on_float_value_is_negative),
            cmocka_unit_test(check_float_to_uintmax_t_error_on_float_value_too_large),
            cmocka_unit_test(check_float_to_uintmax_t_with_rounding_mode_nearest),
            cmocka_unit_test(check_float_to_uintmax_t_with_rounding_mode_downward),
            cmocka_unit_test(check_float_to_uintmax_t_with_rounding_mode_upward),
            cmocka_unit_test(check_float_to_uintmax_t_with_rounding_mode_towards_zero),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
