#ifndef _SEAGRASS_SIZE_T_H_
#define _SEAGRASS_SIZE_T_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL                       1
#define SEAGRASS_SIZE_T_ERROR_RESULT_IS_INCONSISTENT            2

/**
 * @brief Comparison function for size_t*.
 * @param [in] a first size_t*.
 * @param [in] b second size_t*.
 * @return <i>-1</i> if <b>a</b> is <u>less than</u> <b>b</b>,
 * <i>0</i> if <b>a</b> is <u>equal to</u> <b>b</b> or <i>1</i> if <b>a</b> is
 * <u>greater than</u> <b>b</b>.
 * @note If <b>a</b> and <b>b</b> is <i>NULL</i> then abort(3) is called.
 */
int seagrass_size_t_ptr_compare(const size_t *a, const size_t *b);

/**
 * @brief Comparison function for size_t.
 * @param [in] a first size_t.
 * @param [in] b second size_t.
 * @return <i>-1</i> if <b>a</b> is <u>less than</u> <b>b</b>,
 * <i>0</i> if <b>a</b> is <u>equal to</u> <b>b</b> or <i>1</i> if <b>a</b> is
 * <u>greater than</u> <b>b</b>.
 */
int seagrass_size_t_compare(size_t a, size_t b);

/**
 * @brief Add two size_t values together and check for overflow.
 * @param [in] a first size_t.
 * @param [in] b second size_t.
 * @param [out] out where the result is stored if successful.
 * @return On success true otherwise false if an error occurred.
 * @throws SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL if the out is <i>NULL</i>.
 * @throws SEAGRASS_SIZE_T_ERROR_RESULT_IS_INCONSISTENT if the added values'
 * result is not consistent.
 */
bool seagrass_size_t_add(size_t a, size_t b, size_t *out);

/**
 * @brief Multiply two size_t values and check for overflow.
 * @param [in] a first size_t.
 * @param [in] b second size_t.
 * @param [out] out where the result is stored if successful.
 * @return On success true otherwise false if an error occurred.
 * @throws SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL if the out is <i>NULL</i>.
 * @throws SEAGRASS_SIZE_T_ERROR_RESULT_IS_INCONSISTENT if the multiplied
 * values' result is not consistent.
 */
bool seagrass_size_t_multiply(size_t a, size_t b, size_t *out);

#endif /* _SEAGRASS_SIZE_T_H_ */
