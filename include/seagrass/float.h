#ifndef _SEAGRASS_FLOAT_H_
#define _SEAGRASS_FLOAT_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <sea-urchin.h>

#define SEAGRASS_FLOAT_ERROR_OUT_IS_NULL \
    SEA_URCHIN_ERROR_OUT_IS_NULL
#define SEAGRASS_FLOAT_ERROR_ROUNDING_MODE_IS_INVALID \
    SEA_URCHIN_ERROR_VALUE_IS_INVALID
#define SEAGRASS_FLOAT_ERROR_FLOAT_VALUE_TOO_LARGE \
    SEA_URCHIN_ERROR_VALUE_IS_TOO_LARGE
#define SEAGRASS_FLOAT_ERROR_FLOAT_VALUE_IS_NEGATIVE \
    SEA_URCHIN_ERROR_VALUE_IS_NEGATIVE
#define SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT \
    SEA_URCHIN_ERROR_RESULT_IS_INCONSISTENT
#define SEAGRASS_FLOAT_ERROR_RESULT_IS_UNCHANGED \
    SEA_URCHIN_ERROR_RESULT_IS_UNCHANGED
#define SEAGRASS_FLOAT_ERROR_DIVIDE_BY_ZERO \
    SEA_URCHIN_ERROR_DIVIDE_BY_ZERO

/**
 * @brief Comparison function for float*.
 * @param [in] a first float*.
 * @param [in] b second float*.
 * @return <i>-1</i> if <b>a</b> is <u>less than</u> <b>b</b>,
 * <i>0</i> if <b>a</b> is <u>equal to</u> <b>b</b> or <i>1</i> if <b>a</b> is
 * <u>greater than</u> <b>b</b>.
 * @note If <b>a</b> and <b>b</b> is <i>NULL</i> then abort(3) is called.
 */
int seagrass_float_ptr_compare(const float *a, const float *b);

/**
 * @brief Comparison function for float.
 * @param [in] a first float.
 * @param [in] b second float.
 * @return <i>-1</i> if <b>a</b> is <u>less than</u> <b>b</b>,
 * <i>0</i> if <b>a</b> is <u>equal to</u> <b>b</b> or <i>1</i> if <b>a</b> is
 * <u>greater than</u> <b>b</b>.
 */
int seagrass_float_compare(float a, float b);

/**
 * @brief Return the smaller float value.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out receive the smaller between the first or second values.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
int seagrass_float_minimum(float a, float b, float *out);

/**
 * @brief Return the larger float value.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out receive the larger between the first or second values.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
int seagrass_float_maximum(float a, float b, float *out);

/**
 * @brief Add two float values together.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out receive the result of the two added values.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT if the added values'
 * result is not consistent.
 * @throws SEAGRASS_FLOAT_ERROR_RESULT_IS_UNCHANGED if there is expected to be
 * a change in the result, but there was none.
 */
int seagrass_float_add(float a, float b, float *out);

/**
 * @brief Subtract the second value from the first.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out receive the result of the two subtracted values.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT if the subtracted
 * values' result is not consistent.
 * @throws SEAGRASS_FLOAT_ERROR_RESULT_IS_UNCHANGED if there is expected to be
 * a change in the result, but there was none.
 */
int seagrass_float_subtract(float a, float b, float *out);

/**
 * @brief Multiply two float values together.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out receive the result of the two multiplied values.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT if the multiplied
 * values' result is not consistent.
 */
int seagrass_float_multiply(float a, float b, float *out);

/**
 * @brief Divide the first value by the second.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out receive the result of the division operation.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAGRASS_FLOAT_ERROR_DIVIDE_BY_ZERO if b is zero.
 * @throws SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT if the divided value
 * result is not consistent.
 */
int seagrass_float_divide(float a, float b, float *out);

/**
 * @brief Are the two float values considered equal.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out true if they are considered equal, false otherwise.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if the out is <i>NULL</i>.
 */
int seagrass_float_is_equal(float a, float b, bool *out);

/**
 * @brief Is the first value considered greater than the second value.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out true if <b>a</b> is considered greater than <b>b</b>,
 * false otherwise.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
int seagrass_float_is_greater_than(float a, float b, bool *out);

/**
 * @brief Is the first value considered less than the second value.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out true if <b>a</b> is considered less than <b>b</b>,
 * false otherwise.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
int seagrass_float_is_less_than(float a, float b, bool *out);

/**
 * @brief Is the first value considered greater than or equal to the second
 * value.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out true if <b>a</b> is considered greater than or
 * equal to <b>b</b>, false otherwise.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
int seagrass_float_is_greater_or_equal(float a, float b, bool *out);

/**
 * @brief Is the first value considered less than or equal to the second
 * value.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out true if <b>a</b> is considered less than or equal to
 * <b>b</b>, false otherwise.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 */
int seagrass_float_is_less_or_equal(float a, float b, bool *out);

enum seagrass_float_rounding_mode {
/**
 * @verbatim
 * 6.2  -> 6
 * 18.7 -> 19
 * @endverbatim
 */
    SEAGRASS_FLOAT_ROUNDING_MODE_NEAREST = 0,
/**
 * @verbatim
 * 6.2  -> 6
 * 19.7 -> 19
 * @endverbatim
 */
    SEAGRASS_FLOAT_ROUNDING_MODE_DOWNWARD = 1,
/**
 * @verbatim
 * 6.2  -> 7
 * 19.7 -> 20
 * @endverbatim
 */
    SEAGRASS_FLOAT_ROUNDING_MODE_UPWARD = 2,
/**
 * @verbatim
 * 6.2  -> 6
 * 19.7 -> 19
 * @endverbatim
 */
    SEAGRASS_FLOAT_ROUNDING_MODE_TOWARDS_ZERO = 3,
};

/**
 * @brief Convert the float value to a uintmax_t value.
 * @param [in] a float value.
 * @param [in] mode rounding to apply to float in order to convert it to a
 * uintmax_t.
 * @param [out] out receive the uintmax_t value of the float.
 * @return On success <i>0</i>, otherwise an error code.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAGRASS_FLOAT_ERROR_FLOAT_VALUE_IS_NEGATIVE if a is negative.
 * @throws SEAGRASS_FLOAT_ERROR_ROUNDING_MODE_IS_INVALID if mode is not one of
 * rounding modes.
 * @throws SEAGRASS_FLOAT_ERROR_FLOAT_VALUE_TOO_LARGE if a is too large to be
 * stored in a uintmax_t.
 * @see SEAGRASS_FLOAT_ROUNDING_MODE_NEAREST
 * @see SEAGRASS_FLOAT_ROUNDING_MODE_DOWNWARD
 * @see SEAGRASS_FLOAT_ROUNDING_MODE_UPWARD
 * @see SEAGRASS_FLOAT_ROUNDING_MODE_TOWARDS_ZERO
 */
int seagrass_float_to_uintmax_t(float a, enum seagrass_float_rounding_mode mode,
                                uintmax_t *out);

#endif /* _SEAGRASS_FLOAT_H_ */
