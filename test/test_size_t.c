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

int main(int argc, char *argv[]) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(check_size_t_ptr_compare),
            cmocka_unit_test(check_size_t_compare),
            cmocka_unit_test(check_size_t_add_error_on_out_is_null),
            cmocka_unit_test(check_size_t_add_error_on_result_is_inconsistent),
            cmocka_unit_test(check_size_t_add),
            cmocka_unit_test(check_size_t_multiply_error_on_out_is_null),
            cmocka_unit_test(check_size_t_multiply_error_on_result_is_inconsistent),
            cmocka_unit_test(check_size_t_multiply),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
