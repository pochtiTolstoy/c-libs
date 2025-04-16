#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_DECIMAL
#define DECIMAL

#define NUM_BITS 4
#define MANTISSA_BITS (NUM_BITS - 1)
#define MANTISSA_EXT_BITS (MANTISSA_BITS * 2)
#define MANTISSA_MAX_BIT 95
#define MANTISSA_MAX_BIT_BIG_DECIMAL 223
#define BITS_EXP_IDX (NUM_BITS - 1)
#define NUM_BIG_DECIMAL_BITS 8
#define BYTE_SIZE 8
#define BITS_PER_INT 32
#define BITS_BIG_DECIMAL_EXP_IDX 7
#define BITS_EXP_SHIFT 16
#define BITS_EXP_LEN 8
#define BITS_SIGN_SHIFT (BITS_PER_INT - 1)
#define EXP_MAX_VALUE 28
#define MAX_NUM_LEN 29

#define POS_SIGN 0
#define NEG_SIGN 1

#define TRUE 1
#define FALSE 0
#define UNDEFINED -1

typedef enum ERR_CODES {
  OK = 0,
  LARGE = 1,
  SMALL = 2,
  DIV_ZERO = 3,
  INVALID_DATA = 4
} ERR_CODES;

#define BYTE_SHIFT_0 0
#define BYTE_SHIFT_1 8
#define BYTE_SHIFT_2 16
#define BYTE_SHIFT_3 24
#define BYTE_SHIFT_4 32
#define BYTE_MASK 0xFF
#define BYTE_MASK_4 0xFFFFFFFF

#define ACCURACY_FLOAT 7
#define MAX_FLOAT_TO_CONVERT 79228157791897854723898736640.0f
#define MIN_FLOAT_TO_CONVERT \
  0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f

typedef struct {
  unsigned int bits[NUM_BITS];
} s21_decimal;

typedef struct {
  unsigned int bits[NUM_BIG_DECIMAL_BITS];
} s21_big_decimal;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int s21_big_decimal_get_bit(const s21_big_decimal *value, int bit);
void s21_big_decimal_set_bit(s21_big_decimal *num, unsigned int bit,
                             unsigned int value);
int s21_big_decimal_get_sign(const s21_big_decimal *num);
void s21_big_decimal_set_sign(s21_big_decimal *num, int sign_value);
int s21_big_decimal_get_scale(const s21_big_decimal *num);
void s21_big_decimal_set_scale(s21_big_decimal *num, unsigned int scale_value);

int s21_get_bit(const s21_decimal *value, int bit);
void s21_set_bit(s21_decimal *num, unsigned int bit, unsigned int value);
int s21_get_sign(const s21_decimal *num);
void s21_set_sign(s21_decimal *num, int sign_value);
int s21_get_scale(const s21_decimal *num);
void s21_set_scale(s21_decimal *num, unsigned int scale_value);
s21_decimal s21_get_abs(s21_decimal num);

void s21_bitwise_add(const s21_big_decimal *num1, const s21_big_decimal *num2,
                     s21_big_decimal *result);
void s21_bitwise_sub(s21_big_decimal num1, s21_big_decimal num2,
                     s21_big_decimal *result);
int s21_add_or_sub(const s21_decimal *num1, const s21_decimal *num2,
                   s21_decimal *result, int op_sign);
int s21_is_add_or_sub(int sign_num1, int sign_num2, int op_sign);
int s21_get_op_sign_plus_minus(int sign_num1, int sign_num2, int op_sign,
                               int index_greatest);
void s21_divide_mantissa_by_10_big_decimal(s21_big_decimal *num,
                                           uint64_t *remainder);
void s21_divide_mantissa_by_10_decimal(s21_decimal *num,
                                       uint64_t *remainder_output);
int bankers_rounding(s21_big_decimal *num);

void s21_decimal_to_big_decimal(const s21_decimal *src, s21_big_decimal *dst);
void s21_big_decimal_to_decimal(const s21_big_decimal *src, s21_decimal *dst);
void s21_str_to_decimal(const char *str, s21_decimal *dst);

int s21_get_fractional_decimal(s21_decimal value, s21_decimal *result);

int s21_decimal_to_str(s21_decimal number, char *buffer);
int s21_is_valid_decimal(const s21_decimal *number);
void s21_remove_trailing_zeros(s21_decimal *value);

int s21_is_zero(const s21_decimal *num);
void s21_shift_left_big_decimal(s21_big_decimal *num, int shift_value);
void s21_normalize_big_decimals(s21_big_decimal *num1, s21_big_decimal *num2);
uint64_t s21_get_remainder_big_decimal(s21_big_decimal *num);
void s21_make_decimal_empty(s21_decimal *num);
int s21_count_all_digits(s21_decimal num);

#endif
