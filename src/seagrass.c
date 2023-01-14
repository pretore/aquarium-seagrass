#include <stdlib.h>
#include <seagrass.h>

#ifdef TEST
#include <test/cmocka.h>
#endif

void seagrass_required(const void *object) {
    seagrass_required_true(NULL != object);
}

void seagrass_required_true(const int check) {
    if (!check) {
        abort();
    }
}

int seagrass_void_ptr_compare(const void *a, const void *b) {
    if (a == b) {
        return 0;
    } else if (a > b) {
        return 1;
    }
    return (-1);
}
