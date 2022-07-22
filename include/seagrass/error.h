#ifndef _SEAGRASS_ERROR_H_
#define _SEAGRASS_ERROR_H_

#include <stddef.h>
#include <threads.h>

#define SEAGRASS_ERROR_NONE                                 0

extern thread_local size_t seagrass_error;

#endif /* _SEAGRASS_ERROR_H_ */
