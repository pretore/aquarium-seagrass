#ifndef _SEAGRASS_UINTMAX_T_H_
#define _SEAGRASS_UINTMAX_T_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <sea-urchin.h>

#define SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL \
    SEA_URCHIN_ERROR_OUT_IS_NULL
#define SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT \
    SEA_URCHIN_ERROR_RESULT_IS_INCONSISTENT
#define SEAGRASS_UINTMAX_T_ERROR_DIVIDE_BY_ZERO \
    SEA_URCHIN_ERROR_DIVIDE_BY_ZERO
#define SEAGRASS_UINTMAX_T_ERROR_QUOTIENT_IS_NULL \
    SEA_URCHIN_ERROR_VALUE_IS_NULL

/**
 * @brief Comparison function for uintmax_t*.
 * @param [in] a first uintmax_t*.
 * @param [in] b second uintmax_t*.
 * @return <i>-1</i> if <b>a</b> is <u>less than</u> <b>b</b>,
 * <i>0</i> if <b>a</b> is <u>equal to</u> <b>b</b> or <i>1</i> if <b>a</b> is
 * <u>greater than</u> <b>b</b>.
 * @note If <b>a</b> and <b>b</b> is <i>NULL</i> then abort(3) is called.
 */
int seagrass_uintmax_t_ptr_compare(const uintmax_t *a, const uintmax_t *b);

/**
 * @brief Comparison function for uintmax_t.
 * @param [in] a first uintmax_t.
 * @param [in] b second uintmax_t.
 * @return <i>-1</i> if <b>a</b> is <u>less than</u> <b>b</b>,
 * <i>0</i> if <b>a</b> is <u>equal to</u> <b>b</b> or <i>1</i> if <b>a</b> is
 * <u>greater than</u> <b>b</b>.
 */
int seagrass_uintmax_t_compare(uintmax_t a, uintmax_t b);

/**
 * @brief Return the smaller uintmax_t value.
 * @param [in] a first uintmax_t.
 * @param [in] b second uintmax_t.
 * @param [out] out receive the smaller between the first or second values.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws ROCK_ERROR_UNINTMAX_T_OUT_IS_NULL if the out argument is <i>NULL</i>.
 */
int seagrass_uintmax_t_minimum(uintmax_t a, uintmax_t b, uintmax_t *out);

/**
 * @brief Return the larger uintmax_t value.
 * @param [in] a first uintmax_t.
 * @param [in] b second uintmax_t.
 * @param [out] out receive the larger between the first or second values.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
int seagrass_uintmax_t_maximum(uintmax_t a, uintmax_t b, uintmax_t *out);

/**
 * @brief Add two uintmax_t values together.
 * @param [in] a first uintmax_t.
 * @param [in] b second uintmax_t.
 * @param [out] out receive the result of the two added values.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT if the added values'
 * result is not consistent.
 */
int seagrass_uintmax_t_add(uintmax_t a, uintmax_t b, uintmax_t *out);

/**
 * @brief Subtract the second value from the first.
 * @param [in] a first uintmax_t.
 * @param [in] b second uintmax_t.
 * @param [out] out receive the result of the two subtracted values.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT if the subtract
 * values' result is not consistent.
 */
int seagrass_uintmax_t_subtract(uintmax_t a, uintmax_t b, uintmax_t *out);

/**
 * @brief Multiply two uintmax_t values.
 * @param [in] a first uintmax_t.
 * @param [in] b second uintmax_t.
 * @param [out] out receive the result of the two multiplied values.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEAGRASS_UNINTMAX_T_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAGRASS_UINTMAX_T_ERROR_RESULT_IS_INCONSISTENT if the multiplied
 * values' result is not consistent.
 */
int seagrass_uintmax_t_multiply(uintmax_t a, uintmax_t b, uintmax_t *out);

/**
 * @brief Divide the divisor by the dividend.
 * @param [in] divisor uintmax_t divided by dividend.
 * @param [in] dividend uintmax_t used to divide divisor.
 * @param [out] quotient receive the quotient.
 * @param [out] remainder optionally receive the remainder.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEAGRASS_UINTMAX_T_ERROR_QUOTIENT_IS_NULL if quotient is <i>NULL</i>.
 * @throws SEAGRASS_UINTMAX_T_ERROR_DIVIDE_BY_ZERO if dividend is zero.
 */
int seagrass_uintmax_t_divide(uintmax_t divisor, uintmax_t dividend,
                              uintmax_t *quotient, uintmax_t *remainder);

/**
 * @brief Return the times and a half and then even number.
 * @param [in] current whose value is used to calculate the next number.
 * @param [out] out receive the result of times and a half and then even.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEAGRASS_UINTMAX_T_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
int seagrass_uintmax_t_times_and_a_half_even(uintmax_t current,
                                             uintmax_t *out);

#endif /* _SEAGRASS_UINTMAX_T_H_ */
