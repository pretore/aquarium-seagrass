#ifndef _SEAGRASS_TEST_WRAP_H_
#define _SEAGRASS_TEST_WRAP_H_

#ifdef TEST
#include <stdbool.h>

extern bool abort_is_overridden;
void __wrap_abort(void);

#endif /* TEST */

#endif /* _SEAGRASS_TEST_WRAP_H_ */