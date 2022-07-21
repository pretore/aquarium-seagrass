#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "wrap.h"

bool abort_is_overridden = false;
extern void __real_abort(void);
void __wrap_abort(void) {
    if (!abort_is_overridden) {
        __real_abort();
    } else {
        function_called();
    }
}
