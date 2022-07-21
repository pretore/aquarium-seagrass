#ifndef _SEAGRASS_FLOAT_H_
#define _SEAGRASS_FLOAT_H_

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * @verbatim
 * 6.2  -> 6
 * 18.7 -> 19
 * @endverbatim
 */
#define SEAGRASS_FLOAT_ROUNDING_MODE_NEAREST                    0
/**
 * @verbatim
 * 6.2  -> 6
 * 19.7 -> 19
 * @endverbatim
 */
#define SEAGRASS_FLOAT_ROUNDING_MODE_DOWNWARD                   1
/**
 * @verbatim
 * 6.2  -> 7
 * 19.7 -> 20
 * @endverbatim
 */
#define SEAGRASS_FLOAT_ROUNDING_MODE_UPWARD                     2

#define SEAGRASS_FLOAT_ROUNDING_MODE_TOWARDS_ZERO               3

#define SEAGRASS_FLOAT_ERROR_OUT_IS_NULL                        1
#define SEAGRASS_FLOAT_ERROR_MODE_IS_INVALID                    2
#define SEAGRASS_FLOAT_ERROR_FLOAT_VALUE_TOO_LARGE              3
#define SEAGRASS_FLOAT_ERROR_FLOAT_VALUE_IS_NEGATIVE            4
#define SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT             5

/**
 * @brief Comparison function for float*.
 * @param [in] a first float*.
 * @param [in] b second float*.
 * @return <i>-1</i> if <b>a</b> is <u>less than</u> <b>b</b>,
 * <i>0</i> if <b>a</b> is <u>equal to</u> <b>b</b> or <i>1</i> if <b>a</b> is
 * <u>greater than</u> <b>b</b>.
 * @note If <b>a</b> and <b>b</b> is <i>NULL</i> then abort(3) is called.
 */
int seagrass_float_ptr_compare(const float* a, const float* b);

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
 * @brief Retrieve the smaller float value.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out receive the smaller between the first or second values.
 * @return On success true otherwise false if an error occurred.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if the out is <i>NULL</i>.
 */
bool seagrass_float_minimum(float a, float b, float *out);

/**
 * @brief Retrieve the larger float value.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out receive the larger between the first or second values.
 * @return On success true otherwise false if an error occurred.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if the out is <i>NULL</i>.
 */
bool seagrass_float_maximum(float a, float b, float *out);

/**
 * @brief Add two float values together.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out receive the result of the two added values.
 * @return On success true otherwise false if an error occurred.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if the out is <i>NULL</i>.
 * @throws SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT if the added values'
 * result is not consistent.
 */
bool seagrass_float_add(float a, float b, float *out);

/**
 * @brief Multiply two float values together.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out receive the result of the two multiplied values.
 * @return On success true otherwise false if an error occurred.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if the out is <i>NULL</i>.
 * @throws SEAGRASS_FLOAT_ERROR_RESULT_IS_INCONSISTENT if the multiplied
 * values' result is not consistent.
 */
bool seagrass_float_multiply(float a, float b, float *out);

// subtract
// divide

/**
 * @brief Are the two float values considered equal.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out true if they are considered equal, false otherwise.
 * @return On success true otherwise false if an error occurred.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if the out is <i>NULL</i>.
 */
bool seagrass_float_is_equal(float a, float b, bool *out);

/**
 * @brief Is the first value considered greater than the second value.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out true if <b>a</b> is considered greater than <b>b</b>,
 * false otherwise.
 * @return On success true otherwise false if an error occurred.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if the out is <i>NULL</i>.
 */
bool seagrass_float_is_greater_than(float a, float b, bool *out);

/**
 * @brief Is the first value considered less than the second value.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out true if <b>a</b> is considered less than <b>b</b>,
 * false otherwise.
 * @return On success true otherwise false if an error occurred.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if the out is <i>NULL</i>.
 */
bool seagrass_float_is_less_than(float a, float b, bool *out);

/**
 * @brief Is the first value considered greater than or equal to the second
 * value.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out true if <b>a</b> is considered greater than or
 * equal to <b>b</b>, false otherwise.
 * @return On success true otherwise false if an error occurred.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if the out is <i>NULL</i>.
 */
bool seagrass_float_is_greater_or_equal(float a, float b, bool *out);

/**
 * @brief Is the first value considered less than or equal to the second
 * value.
 * @param [in] a first float.
 * @param [in] b second float.
 * @param [out] out true if <b>a</b> is considered less than or equal to
 * <b>b</b>, false otherwise.
 * @return On success true otherwise false if an error occurred.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if the out is <i>NULL</i>.
 */
bool seagrass_float_is_less_or_equal(float a, float b, bool *out);

/**
 * @brief Convert the float value to a size_t value.
 * @param [in] a float value.
 * @param [in] mode rounding to apply to float in order to convert it to a
 * size_t.
 * @param [out] out receive the size_t value of the float.
 * @return On success true otherwise false if an error occurred.
 * @throws SEAGRASS_FLOAT_ERROR_OUT_IS_NULL if out is <i>NULL</i>.
 * @throws SEAGRASS_FLOAT_ERROR_FLOAT_VALUE_IS_NEGATIVE if a is negative.
 * @throws SEAGRASS_FLOAT_ERROR_MODE_IS_INVALID if mode is not one of
 * rounding modes.
 * @throws SEAGRASS_FLOAT_ERROR_FLOAT_VALUE_TOO_LARGE if a is too large to be
 * stored in a size_t.
 * @see SEAGRASS_FLOAT_ROUNDING_MODE_NEAREST
 * @see SEAGRASS_FLOAT_ROUNDING_MODE_DOWNWARD
 * @see SEAGRASS_FLOAT_ROUNDING_MODE_UPWARD
 * @see SEAGRASS_FLOAT_ROUNDING_MODE_TOWARDS_ZERO
 */
bool seagrass_float_to_size_t(float a, size_t mode, size_t *out);

#endif /* _SEAGRASS_FLOAT_H_ */
