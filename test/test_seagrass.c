#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <seagrass.h>

#include <test/cmocka.h>

static void check_required(void **state) {
    abort_is_overridden = true;
    seagrass_required((void *)1);
    expect_function_call(cmocka_test_abort);
    seagrass_required(NULL);
    abort_is_overridden = false;
}

static void check_required_true(void **state) {
    abort_is_overridden = true;
    seagrass_required_true(true);
    expect_function_call(cmocka_test_abort);
    seagrass_required_true(false);
    abort_is_overridden = false;
}

static void check_void_ptr_compare(void **state) {
    const void* i[] = {
            NULL,
            (void *) 1
    };
    assert_int_equal((-1), seagrass_void_ptr_compare(i[0], i[1]));
    assert_int_equal(0, seagrass_void_ptr_compare(i[0], i[0]));
    assert_int_equal(0, seagrass_void_ptr_compare(i[1], i[1]));
    assert_int_equal(1, seagrass_void_ptr_compare(i[1], i[0]));
}

int main(int argc, char *argv[]) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(check_required),
            cmocka_unit_test(check_required_true),
            cmocka_unit_test(check_void_ptr_compare),
    };
    //cmocka_set_message_output(CM_OUTPUT_XML);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
