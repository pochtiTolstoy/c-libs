#include "arithmetic.h"
#include "s21_decimal.h"

static void s21_mul_mantissa_(const uint32_t *, const uint32_t *, uint32_t *);

static void s21_reduce_lhs(uint32_t *, int *, uint32_t *);

int s21_mul(s21_decimal lhs, s21_decimal rhs, s21_decimal *res) {
  if (!res || !s21_is_valid_decimal(&lhs) || !s21_is_valid_decimal(&rhs)) {
    return INVALID_DATA;
  }
  uint32_t last_digit = 0;
  int res_sign = s21_get_sign(&lhs) ^ s21_get_sign(&rhs);
  int scale = s21_get_scale(&lhs) + s21_get_scale(&rhs);
  s21_make_decimal_empty(res);
  uint32_t extended_bits[MANTISSA_EXT_BITS] = {0};
  s21_mul_mantissa_(lhs.bits, rhs.bits, extended_bits);
  s21_reduce_lhs(extended_bits, &scale, &last_digit);
  s21_bank_rounding(extended_bits, last_digit);
  int overflow = s21_is_overflow_extended(extended_bits);
  ERR_CODES code = OK;
  if (!overflow) {
    memcpy(res->bits, extended_bits, sizeof(uint32_t) * MANTISSA_BITS);
    s21_set_sign(res, res_sign);
    s21_set_scale(res, scale);
  } else {
    code = (res_sign) ? SMALL : LARGE;
  }
  if (s21_is_zero(res)) {
    s21_set_scale(res, 0);
    s21_set_sign(res, POS_SIGN);
  }
  return code;
}

static void s21_mul_mantissa_(const uint32_t *lhs, const uint32_t *rhs,
                              uint32_t *res) {
  for (int i = 0; i < MANTISSA_BITS; ++i) {
    for (int j = 0; j < MANTISSA_BITS; ++j) {
      uint64_t product = (uint64_t)lhs[i] * rhs[j];

      uint32_t low_product = (uint32_t)product;
      uint32_t carry_product = (uint32_t)(product >> BYTE_SHIFT_4);

      int curr_cell = i + j;

      uint64_t sum = (uint64_t)res[curr_cell] + low_product;
      res[curr_cell] = (uint32_t)sum;
      uint32_t carry_sum = (uint32_t)(sum >> BYTE_SHIFT_4);

      sum = (uint64_t)res[curr_cell + 1] + carry_product + carry_sum;
      res[curr_cell + 1] = (uint64_t)sum;
      carry_sum = (uint32_t)(sum >> BYTE_SHIFT_4);

      int cell = curr_cell + 2;
      for (; cell < MANTISSA_EXT_BITS && carry_sum; ++cell) {
        sum = (uint64_t)res[cell] + carry_sum;
        res[cell] = (uint32_t)(sum);
        carry_sum = (uint32_t)(sum >> BYTE_SHIFT_4);
      }
    }
  }
}

static void s21_reduce_lhs(uint32_t *extended_bits, int *scale,
                           uint32_t *last_digit) {
  int overflow = s21_is_overflow_extended(extended_bits);
  int rem2 = 0;
  int is_tail_rem = 0;
  int while_iter = 0;
  while ((overflow || *scale > EXP_MAX_VALUE) && *scale) {
    s21_div_by_10_extended(extended_bits, last_digit);
    int rem1 = rem2;
    if (rem1) {
      is_tail_rem = 1;
    }
    rem2 = *last_digit;
    overflow = s21_is_overflow_extended(extended_bits);
    ++while_iter;
    --(*scale);
  }
  if (while_iter > 1 && is_tail_rem && *last_digit == 5) {
    *last_digit = 6;
  }
}
