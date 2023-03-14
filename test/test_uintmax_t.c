#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <seagrass.h>

#include <test/cmocka.h>

static void check_uintmax_t_ptr_compare(void **state) {
    const uintmax_t q[] = {
            0,
            1
    };
    const uintmax_t *i[] = {
            &q[0],
            &q[1]
    };
    assert_int_equal((-1), seagrass_uintmax_t_ptr_compare(i[0], i[1]));
    assert_int_equal((-1), seagrass_uintmax_t_ptr_compare(i[1], NULL));
    assert_int_equal((-1), seagrass_uintmax_t_ptr_compare(i[0], NULL));
    assert_int_equal(0, seagrass_uintmax_t_ptr_compare(i[0], i[0]));
    assert_int_equal(0, seagrass_uintmax_t_ptr_compare(i[1], i[1]));
    assert_int_equal(1, seagrass_uintmax_t_ptr_compare(i[1], i[0]));
    assert_int_equal(1, seagrass_uintmax_t_ptr_compare(NULL, i[0]));
    assert_int_equal(1, seagrass_uintmax_t_ptr_compare(NULL, i[1]));

    abort_is_overridden = true;
    expect_function_call(cmocka_test_abort);
    seagrass_uintmax_t_ptr_compare(NULL, NULL);
    abort_is_overridden = false;
}

static void check_uintmax_t_compare(void **state) {
    const uintmax_t i[] = {
            0,
            1
    };
    assert_int_equal((-1), seagrass_uintmax_t_compare(i[0], i[1]));
    assert_int_equal(0, seagrass_uintmax_t_compare(i[0], i[0]));
    assert_int_equal(0, seagrass_uintmax_t_compare(i[1], i[1]));
    assert_int_equal(1, seagrass_uintmax_t_compare(i[1], i[0]));
}

static void check_uintmax_t_minimum_error_on_out_is_null(void **state) {
    assert_int_equal(
            seagrass_uintmax_t_minimum(1, 1, NULL),
            SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL);
}

static void check_uintmax_t_minimum(void **state) {
    uintmax_t result;
    assert_int_equal(
            seagrass_uintmax_t_minimum(1, UINTMAX_MAX, &result), 0);
    assert_int_equal(1, result);
    assert_int_equal(
            seagrass_uintmax_t_minimum(UINTMAX_MAX, 10, &result), 0);
    assert_int_equal(10, result);
}

static void check_uintmax_t_maximum_error_on_out_is_null(void **state) {
    assert_int_equal(
            seagrass_uintmax_t_maximum(1, 1, NULL),
            SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL);
}

static void check_uintmax_t_maximum(void **state) {
    uintmax_t result;
    assert_int_equal(
            seagrass_uintmax_t_maximum(32, 121, &result), 0);
    assert_int_equal(121, result);
    assert_int_equal(
            seagrass_uintmax_t_maximum(UINTMAX_MAX, 21, &result), 0);
    assert_int_equal(UINTMAX_MAX, result);
}

static void check_uintmax_t_add_error_on_out_is_null(void **state) {
    assert_int_equal(
            seagrass_uintmax_t_add(0, 1, NULL),
            SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL);
}

static void check_uintmax_t_add_error_on_result_is_inconsistent(void **state) {
    uintmax_t result;
    assert_int_equal(
            seagrass_uintmax_t_add(UINTMAX_MAX, 1, &result),
            SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT);
}

static void check_uintmax_t_add(void **state) {
    uintmax_t result;
    assert_int_equal(
            seagrass_uintmax_t_add(0, 1, &result), 0);
    assert_int_equal(1, result);
}

static void check_uintmax_t_subtract_error_on_out_is_null(void **state) {
    assert_int_equal(
            seagrass_uintmax_t_subtract(1, 1, NULL),
            SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL);
}

static void
check_uintmax_t_subtract_error_on_result_is_inconsistent(void **state) {
    assert_int_equal(
            seagrass_uintmax_t_subtract(0, UINTMAX_MAX, (void *) 1),
            SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT);
}

static void check_uintmax_t_subtract(void **state) {
    uintmax_t result;
    assert_int_equal(
            seagrass_uintmax_t_subtract(0, 0, &result), 0);
    assert_int_equal(0, result);
    assert_int_equal(
            seagrass_uintmax_t_subtract(UINTMAX_MAX, UINTMAX_MAX,&result), 0);
    assert_int_equal(0, result);
    assert_int_equal(
            seagrass_uintmax_t_subtract(100, 99, &result), 0);
    assert_int_equal(1, result);
}

static void check_uintmax_t_multiply_error_on_out_is_null(void **state) {
    assert_int_equal(
            seagrass_uintmax_t_multiply(1, 3, NULL),
            SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL);
}

static void
check_uintmax_t_multiply_error_on_result_is_inconsistent(void **state) {
    uintmax_t result;
    assert_int_equal(
            seagrass_uintmax_t_multiply(2, UINTMAX_MAX, &result),
            SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT);
}

static void check_uintmax_t_multiply(void **state) {
    uintmax_t result;
    assert_int_equal(
            seagrass_uintmax_t_multiply(0, UINTMAX_MAX, &result), 0);
    assert_int_equal(0, result);
    assert_int_equal(
            seagrass_uintmax_t_multiply(UINTMAX_MAX, 0, &result), 0);
    assert_int_equal(0, result);
    assert_int_equal(
            seagrass_uintmax_t_multiply(2, 2, &result), 0);
    assert_int_equal(4, result);
}

static void check_uintmax_t_divide_error_on_quotient_is_null(void **state) {
    assert_int_equal(
            seagrass_uintmax_t_divide(1, 1, NULL, (void *) 1),
            SEAGRASS_UINTMAX_T_ERROR_QUOTIENT_IS_NULL);
}

static void check_uintmax_t_divide_error_on_divide_by_zero(void **state) {
    assert_int_equal(
            seagrass_uintmax_t_divide(1, 0, (void *) 1, (void *) 1),
            SEAGRASS_UINTMAX_T_ERROR_DIVIDE_BY_ZERO);
}

static void check_uintmax_t_divide(void **state) {
    uintmax_t quotient, remainder;
    assert_int_equal(
            seagrass_uintmax_t_divide(0, 1, &quotient, NULL), 0);
    assert_int_equal(0, quotient);
    assert_int_equal(
            seagrass_uintmax_t_divide(SIZE_MAX, 1, &quotient, NULL), 0);
    assert_int_equal(UINTMAX_MAX, quotient);
    assert_int_equal(
            seagrass_uintmax_t_divide(22, 5, &quotient, &remainder), 0);
    assert_int_equal(4, quotient);
    assert_int_equal(2, remainder);
}

static void
check_uintmax_t_times_and_a_half_even_error_on_out_is_null(void **state) {
    assert_int_equal(
            seagrass_uintmax_t_times_and_a_half_even(0, NULL),
            SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL);
}

static void check_uintmax_t_times_and_a_half_even(void **state) {
    struct pair {
        uintmax_t in;
        uintmax_t out;
    };
    struct pair pairs[] = {
            {0,    2},
            {2,    4},
            {4,    6},
            {6,    10},
            {10,   16},
            {16,   24},
            {24,   36},
            {36,   54},
            {54,   82},
            {82,   124},
            {124,  186},
            {186,  280},
            {280,  420},
            {420,  630},
            {630,  946},
            {946,  1420},
            {1420, 2130}
    };
    const uintmax_t count = sizeof(pairs) / sizeof(struct pair);
    for (uintmax_t i = 0; i < count; i++) {
        const struct pair p = pairs[i];
        uintmax_t out;
        assert_true(seagrass_uintmax_t_times_and_a_half_even(p.in, &out));
        assert_int_equal(p.out, out);
    }
}

int main(int argc, char *argv[]) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(check_uintmax_t_ptr_compare),
            cmocka_unit_test(check_uintmax_t_compare),
            cmocka_unit_test(check_uintmax_t_minimum_error_on_out_is_null),
            cmocka_unit_test(check_uintmax_t_minimum),
            cmocka_unit_test(check_uintmax_t_maximum_error_on_out_is_null),
            cmocka_unit_test(check_uintmax_t_maximum),
            cmocka_unit_test(check_uintmax_t_add_error_on_out_is_null),
            cmocka_unit_test(check_uintmax_t_add_error_on_result_is_inconsistent),
            cmocka_unit_test(check_uintmax_t_add),
            cmocka_unit_test(check_uintmax_t_subtract_error_on_out_is_null),
            cmocka_unit_test(check_uintmax_t_subtract_error_on_result_is_inconsistent),
            cmocka_unit_test(check_uintmax_t_subtract),
            cmocka_unit_test(check_uintmax_t_multiply_error_on_out_is_null),
            cmocka_unit_test(check_uintmax_t_multiply_error_on_result_is_inconsistent),
            cmocka_unit_test(check_uintmax_t_multiply),
            cmocka_unit_test(check_uintmax_t_divide_error_on_quotient_is_null),
            cmocka_unit_test(check_uintmax_t_divide_error_on_divide_by_zero),
            cmocka_unit_test(check_uintmax_t_divide),
            cmocka_unit_test(check_uintmax_t_times_and_a_half_even_error_on_out_is_null),
            cmocka_unit_test(check_uintmax_t_times_and_a_half_even),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
