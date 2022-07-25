#ifndef _SEAGRASS_SIZE_T_H_
#define _SEAGRASS_SIZE_T_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL                       1
#define SEAGRASS_SIZE_T_ERROR_RESULT_IS_INCONSISTENT            2
#define SEAGRASS_SIZE_T_ERROR_DIVIDE_BY_ZERO                    3
#define SEAGRASS_SIZE_T_ERROR_QUOTIENT_IS_NULL                  4

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
 * @brief Return the smaller size_t value.
 * @param [in] a first size_t.
 * @param [in] b second size_t.
 * @param [out] out receive the smaller between the first or second values.
 * @return On success true otherwise false if an error occurred.
 * @throws ROCK_ERROR_OUT_IS_NULL if the out argument is <i>NULL</i>.
 */
bool seagrass_size_t_minimum(size_t a, size_t b, size_t *out);

/**
 * @brief Return the larger size_t value.
 * @param [in] a first size_t.
 * @param [in] b second size_t.
 * @param [out] out receive the larger between the first or second values.
 * @return On success true otherwise false if an error occurred.
 * @throws SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
bool seagrass_size_t_maximum(size_t a, size_t b, size_t *out);

/**
 * @brief Add two size_t values together.
 * @param [in] a first size_t.
 * @param [in] b second size_t.
 * @param [out] out receive the result of the two added values.
 * @return On success true otherwise false if an error occurred.
 * @throws SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAGRASS_SIZE_T_ERROR_RESULT_IS_INCONSISTENT if the added values'
 * result is not consistent.
 */
bool seagrass_size_t_add(size_t a, size_t b, size_t *out);

/**
 * @brief Subtract the second value from the first.
 * @param [in] a first size_t.
 * @param [in] b second size_t.
 * @param [out] out receive the result of the two subtracted values.
 * @return On success true otherwise false if an error occurred.
 * @throws SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAGRASS_SIZE_T_ERROR_RESULT_IS_INCONSISTENT if the subtract
 * values' result is not consistent.
 */
bool seagrass_size_t_subtract(size_t a, size_t b, size_t *out);

/**
 * @brief Multiply two size_t values.
 * @param [in] a first size_t.
 * @param [in] b second size_t.
 * @param [out] out receive the result of the two multiplied values.
 * @return On success true otherwise false if an error occurred.
 * @throws SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAGRASS_SIZE_T_ERROR_RESULT_IS_INCONSISTENT if the multiplied
 * values' result is not consistent.
 */
bool seagrass_size_t_multiply(size_t a, size_t b, size_t *out);

/**
 * @brief Divide the divisor by the dividend.
 * @param [in] divisor size_t divided by dividend.
 * @param [in] dividend size_t used to divide divisor.
 * @param [out] quotient receive the quotient.
 * @param [out] remainder optionally receive the remainder.
 * @return On success true otherwise false if an error occurred.
 * @throws SEAGRASS_SIZE_T_ERROR_QUOTIENT_IS_NULL if quotient is <i>NULL</i>.
 * @throws SEAGRASS_SIZE_T_ERROR_DIVIDE_BY_ZERO if b is zero.
 */
bool seagrass_size_t_divide(size_t divisor, size_t dividend, size_t *quotient,
                            size_t *remainder);

/**
 * @brief Return the times and a half and then even number.
 * @param [in] current whose value is used to calculate the next number.
 * @param [out] out receive the result of times and a half and then even.
 * @return On success true otherwise false if an error occurred.
 * @throws SEAGRASS_SIZE_T_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
bool seagrass_size_t_times_and_a_half_even(size_t current, size_t *out);

#endif /* _SEAGRASS_SIZE_T_H_ */
