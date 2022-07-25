#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <seagrass.h>

#include "test/cmocka.h"
#include "test/wrap.h"

static void check_size_t_ptr_compare(void **state) {
    const size_t q[] = {
            0,
            1
    };
    const size_t* i[] = {
            &q[0],
            &q[1]
    };
    assert_int_equal((-1), seagrass_size_t_ptr_compare(i[0], i[1]));
    assert_int_equal((-1), seagrass_size_t_ptr_compare(i[1], NULL));
    assert_int_equal((-1), seagrass_size_t_ptr_compare(i[0], NULL));
    assert_int_equal(0, seagrass_size_t_ptr_compare(i[0], i[0]));
    assert_int_equal(0, seagrass_size_t_ptr_compare(i[1], i[1]));
    assert_int_equal(1, seagrass_size_t_ptr_compare(i[1], i[0]));
    assert_int_equal(1, seagrass_size_t_ptr_compare(NULL, i[0]));
    assert_int_equal(1, seagrass_size_t_ptr_compare(NULL, i[1]));

    abort_is_overridden = true;
    expect_function_call(__wrap_abort);
    seagrass_size_t_ptr_compare(NULL, NULL);
    abort_is_overridden = false;
}

static void check_size_t_compare(void **state) {
    const size_t i[] = {
            0,
            1
    };
    assert_int_equal((-1), seagrass_size_t_compare(i[0], i[1]));
    assert_int_equal(0, seagrass_size_t_compare(i[0], i[0]));
    assert_int_equal(0, seagrass_size_t_compare(i[1], i[1]));
    assert_int_equal(1, seagrass_size_t_compare(i[1], i[0]));
}

static void check_size_t_minimum_error_on_out_is_null(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_size_t_minimum(1, 1, NULL));
    assert_int_equal(SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_size_t_minimum(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    size_t result;
    assert_true(seagrass_size_t_minimum(1, SIZE_MAX, &result));
    assert_int_equal(1, result);
    assert_true(seagrass_size_t_minimum(SIZE_MAX, 10, &result));
    assert_int_equal(10, result);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_size_t_maximum_error_on_out_is_null(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_size_t_maximum(1, 1, NULL));
    assert_int_equal(SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_size_t_maximum(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    size_t result;
    assert_true(seagrass_size_t_maximum(32, 121, &result));
    assert_int_equal(121, result);
    assert_true(seagrass_size_t_maximum(SIZE_MAX, 21, &result));
    assert_int_equal(SIZE_MAX, result);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_size_t_add_error_on_out_is_null(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_size_t_add(0, 1, NULL));
    assert_int_equal(SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_size_t_add_error_on_result_is_inconsistent(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    size_t result;
    assert_false(seagrass_size_t_add(SIZE_MAX, 1, &result));
    assert_int_equal(SEAGRASS_SIZE_T_ERROR_RESULT_IS_INCONSISTENT, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_size_t_add(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    size_t result;
    assert_true(seagrass_size_t_add(0, 1, &result));
    assert_int_equal(1, result);
    seagrass_error = SEAGRASS_ERROR_NONE;
}


static void check_size_t_subtract_error_on_out_is_null(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_size_t_subtract(1, 1, NULL));
    assert_int_equal(SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void
check_size_t_subtract_error_on_result_is_inconsistent(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_size_t_subtract(0, SIZE_MAX, (void *)1));
    assert_int_equal(SEAGRASS_SIZE_T_ERROR_RESULT_IS_INCONSISTENT,
                     seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_size_t_subtract(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    size_t result;
    assert_true(seagrass_size_t_subtract(0, 0, &result));
    assert_int_equal(0, result);
    assert_true(seagrass_size_t_subtract(SIZE_MAX, SIZE_MAX, &result));
    assert_int_equal(0, result);
    assert_true(seagrass_size_t_subtract(100, 99, &result));
    assert_int_equal(1, result);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_size_t_multiply_error_on_out_is_null(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_size_t_multiply(1, 3, NULL));
    assert_int_equal(SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void
check_size_t_multiply_error_on_result_is_inconsistent(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    size_t result;
    assert_false(seagrass_size_t_multiply(2, SIZE_MAX, &result));
    assert_int_equal(SEAGRASS_SIZE_T_ERROR_RESULT_IS_INCONSISTENT, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_size_t_multiply(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    size_t result;
    assert_true(seagrass_size_t_multiply(0, SIZE_MAX, &result));
    assert_int_equal(0, result);
    assert_true(seagrass_size_t_multiply(SIZE_MAX, 0, &result));
    assert_int_equal(0, result);
    assert_true(seagrass_size_t_multiply(2, 2, &result));
    assert_int_equal(4, result);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_size_t_divide_error_on_quotient_is_null(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_size_t_divide(1, 1, NULL, (void *)1));
    assert_int_equal(SEAGRASS_SIZE_T_ERROR_QUOTIENT_IS_NULL, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_size_t_divide_error_on_divide_by_zero(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_size_t_divide(1, 0, (void *)1, (void *)1));
    assert_int_equal(SEAGRASS_SIZE_T_ERROR_DIVIDE_BY_ZERO, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_size_t_divide(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    size_t quotient, remainder;
    assert_true(seagrass_size_t_divide(0, 1, &quotient, NULL));
    assert_int_equal(0, quotient);
    assert_true(seagrass_size_t_divide(SIZE_MAX, 1, &quotient, NULL));
    assert_int_equal(SIZE_MAX, quotient);
    assert_true(seagrass_size_t_divide(22, 5, &quotient, &remainder));
    assert_int_equal(4, quotient);
    assert_int_equal(2, remainder);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void
check_size_t_times_and_a_half_even_error_on_out_is_null(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    assert_false(seagrass_size_t_times_and_a_half_even(0, NULL));
    assert_int_equal(SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL, seagrass_error);
    seagrass_error = SEAGRASS_ERROR_NONE;
}

static void check_size_t_times_and_a_half_even(void **state) {
    seagrass_error = SEAGRASS_ERROR_NONE;
    struct pair_t {
        size_t in;
        size_t out;
    };
    struct pair_t pairs[] = {
            {0, 2},
            {2, 4},
            {4, 6},
            {6, 10},
            {10, 16},
            {16, 24},
            {24, 36},
            {36, 54},
            {54, 82},
            {82, 124},
            {124, 186},
            {186, 280},
            {280, 420},
            {420, 630},
            {630, 946},
            {946, 1420},
            {1420, 2130}
    };
    const size_t count = sizeof(pairs) / sizeof(struct pair_t);
    for (size_t i = 0; i < count; i++) {
        const struct pair_t p = pairs[i];
        size_t out;
        assert_true(seagrass_size_t_times_and_a_half_even(p.in, &out));
        assert_int_equal(p.out, out);
    }
    seagrass_error = SEAGRASS_ERROR_NONE;
}

int main(int argc, char *argv[]) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(check_size_t_ptr_compare),
            cmocka_unit_test(check_size_t_compare),
            cmocka_unit_test(check_size_t_minimum_error_on_out_is_null),
            cmocka_unit_test(check_size_t_minimum),
            cmocka_unit_test(check_size_t_maximum_error_on_out_is_null),
            cmocka_unit_test(check_size_t_maximum),
            cmocka_unit_test(check_size_t_add_error_on_out_is_null),
            cmocka_unit_test(check_size_t_add_error_on_result_is_inconsistent),
            cmocka_unit_test(check_size_t_add),
            cmocka_unit_test(check_size_t_subtract_error_on_out_is_null),
            cmocka_unit_test(check_size_t_subtract_error_on_result_is_inconsistent),
            cmocka_unit_test(check_size_t_subtract),
            cmocka_unit_test(check_size_t_multiply_error_on_out_is_null),
            cmocka_unit_test(check_size_t_multiply_error_on_result_is_inconsistent),
            cmocka_unit_test(check_size_t_multiply),
            cmocka_unit_test(check_size_t_divide_error_on_quotient_is_null),
            cmocka_unit_test(check_size_t_divide_error_on_divide_by_zero),
            cmocka_unit_test(check_size_t_divide),
            cmocka_unit_test(check_size_t_times_and_a_half_even_error_on_out_is_null),
            cmocka_unit_test(check_size_t_times_and_a_half_even),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
