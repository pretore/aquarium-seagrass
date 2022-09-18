#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <errno.h>

#include "cmocka.h"

extern void *_test_malloc(size_t size, const char *file, int line);
bool malloc_is_overridden = false;
void *cmocka_test_malloc(const size_t size, const char *file, const int line) {
    if (malloc_is_overridden) {
        errno = ENOMEM;
        return NULL;
    }
    return _test_malloc(size, file, line);
}

extern void *
_test_calloc(size_t nmemb, size_t size, const char *file, int line);
bool calloc_is_overridden = false;
void *
cmocka_test_calloc(const size_t nmemb, const size_t size, const char *file,
                   const int line) {
    if (calloc_is_overridden) {
        errno = ENOMEM;
        return NULL;
    }
    return _test_calloc(nmemb, size, file, line);
}

extern void *
_test_realloc(void *ptr, size_t size, const char *file, int line);
bool realloc_is_overridden = false;
void *
cmocka_test_realloc(void *ptr, const size_t size, const char *file,
                    const int line) {
    if (realloc_is_overridden) {
        errno = ENOMEM;
        return NULL;
    }
    return _test_realloc(ptr, size, file, line);
}

extern void _test_free(void* ptr, const char* file, int line);
void cmocka_test_free(void *ptr, const char *file, const int line) {
    _test_free(ptr, file, line);
}

#undef abort
bool abort_is_overridden = false;
void cmocka_test_abort(const char *file, const int line) {
    if (abort_is_overridden) {
        function_called();
    } else {
        abort();
    }
}
