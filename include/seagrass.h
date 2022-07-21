#ifndef _SEAGRASS_SEAGRASS_H_
#define _SEAGRASS_SEAGRASS_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include <seagrass/error.h>
#include <seagrass/float.h>
#include <seagrass/size_t.h>

/**
 * @brief Require that object be non-<i>NULL</i>.
 * @param [in] object to check if it is non-<i>NULL</i>.
 * @note Will call abort(3) if object is <i>NULL</i>.
 */
void seagrass_required(const void *object);

/**
 * @brief Require true evaluation.
 * @param [in] check to see if it is true.
 * @note Will call abort(3) if check is false.
 */
void seagrass_required_true(int check);

/**
 * @brief Comparison function for void*.
 * @param [in] a first void*.
 * @param [in] b second void*.
 * @return <i>-1</i> if <b>a</b> is <u>less than</u> <b>b</b>,
 * <i>0</i> if <b>a</b> is <u>equal to</u> <b>b</b> or <i>1</i> if <b>a</b> is
 * <u>greater than</u> <b>b</b>.
 */
int seagrass_void_ptr_compare(const void *a, const void *b);

#endif /* _SEAGRASS_SEAGRASS_H_ */
