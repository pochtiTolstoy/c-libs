#include "arithmetic.h"
#include "s21_decimal.h"

static int s21_mul_extended(const uint32_t *, const uint32_t *, uint32_t *);

static void s21_maximize_extended(uint32_t *, int *);

static void s21_reduce_lhs(uint32_t *, int *, uint32_t *);

static void s21_extract_rem(uint32_t *, const uint32_t *);

static int s21_is_empty_extended(const uint32_t *);

int s21_div(s21_decimal lhs, s21_decimal rhs, s21_decimal *res) {
  s21_make_decimal_empty(res);
  s21_remove_trailing_zeros(&lhs);
  s21_remove_trailing_zeros(&rhs);
  ERR_CODES code = (s21_is_zero(&rhs)) ? DIV_ZERO : OK;
  if (code == OK && !s21_is_zero(&lhs)) {
    uint32_t lhs_extended[MANTISSA_EXT_BITS] = {0};
    uint32_t rhs_extended[MANTISSA_EXT_BITS] = {0};
    uint32_t remainder[MANTISSA_EXT_BITS] = {0};
    memcpy(lhs_extended, lhs.bits, sizeof(uint32_t) * MANTISSA_BITS);
    memcpy(rhs_extended, rhs.bits, sizeof(uint32_t) * MANTISSA_BITS);
    int new_sign = s21_get_sign(&lhs) ^ s21_get_sign(&rhs);
    int new_scale = s21_get_scale(&lhs) - s21_get_scale(&rhs);
    s21_maximize_extended(lhs_extended, &new_scale);
    s21_div_maximized_extended(lhs_extended, rhs_extended, remainder);
    s21_extract_rem(remainder, rhs_extended);
    s21_reduce_lhs(lhs_extended, &new_scale, remainder);
    uint32_t last_digit = remainder[0];
    s21_bank_rounding(lhs_extended, last_digit);
    if (!s21_is_overflow_extended(lhs_extended)) {
      memcpy(res->bits, lhs_extended, sizeof(uint32_t) * MANTISSA_BITS);
      s21_set_scale(res, new_scale);
      s21_set_sign(res, new_sign);
      s21_remove_trailing_zeros(res);
    } else {
      code = (new_sign) ? SMALL : LARGE;
    }
  }
  return code;
}

static void s21_maximize_extended(uint32_t *extended, int *scale) {
  uint32_t maximized[MANTISSA_EXT_BITS] = {0};
  uint32_t extended_ten[MANTISSA_EXT_BITS] = {10};
  while (s21_mul_extended(extended, extended_ten, maximized) == OK) {
    memcpy(extended, maximized, sizeof(maximized));
    ++(*scale);
  }
}

static int s21_mul_extended(const uint32_t *lhs, const uint32_t *rhs,
                            uint32_t *res) {
  uint32_t product_carry = 0;
  uint32_t sum_carry = 0;
  memset(res, 0, sizeof(*res) * MANTISSA_EXT_BITS);
  for (size_t i = 0; i < MANTISSA_EXT_BITS; ++i) {
    sum_carry = product_carry = 0;
    for (size_t j = 0; j + i < MANTISSA_EXT_BITS; ++j) {
      int curr_cell = i + j;
      uint64_t product = (uint64_t)lhs[i] * rhs[j] + product_carry + sum_carry;
      uint32_t low_product = (uint32_t)(product);
      uint32_t high_product = (uint32_t)(product >> BYTE_SHIFT_4);
      product_carry = high_product;
      uint64_t sum = low_product + res[curr_cell];
      sum_carry = (uint32_t)(sum >> BYTE_SHIFT_4);
      res[curr_cell] = (uint32_t)(sum);
    }
  }
  return (product_carry || sum_carry) ? (ERR_CODES)LARGE : (ERR_CODES)OK;
}

static void s21_reduce_lhs(uint32_t *lhs_extended, int *new_scale,
                           uint32_t *remainder) {
  const uint32_t ten_value[MANTISSA_EXT_BITS] = {10};
  int is_old_rem = !s21_is_empty_extended(remainder);
  int is_overflow = s21_is_overflow_extended(lhs_extended);
  int rem2 = 0;
  int while_iter = 0;
  int is_tail_rem = 0;
  while ((is_overflow || *new_scale > EXP_MAX_VALUE) && *new_scale) {
    s21_div_maximized_extended(lhs_extended, ten_value, remainder);
    int rem1 = rem2;
    if (rem1) is_tail_rem = 1;
    rem2 = remainder[0];
    is_overflow = s21_is_overflow_extended(lhs_extended);
    ++while_iter;
    --(*new_scale);
  }
  if (((while_iter > 1 && is_tail_rem) || is_old_rem) && remainder[0] == 5) {
    remainder[0] = 6;
  }
}

static void s21_extract_rem(uint32_t *remainder, const uint32_t *divisor) {
  const uint32_t ten_value[MANTISSA_EXT_BITS] = {10};
  uint32_t extra_rem[MANTISSA_EXT_BITS] = {0};
  uint32_t temp_rem[MANTISSA_EXT_BITS] = {0};
  s21_mul_extended(remainder, ten_value, extra_rem);
  s21_div_maximized_extended(extra_rem, divisor, temp_rem);
  if ((!s21_is_empty_extended(temp_rem)) && extra_rem[0] == 5) {
    extra_rem[0] = 6;
  }
  memset(remainder, 0, sizeof(uint32_t) * MANTISSA_EXT_BITS);
  remainder[0] = extra_rem[0];
}

static int s21_is_empty_extended(const uint32_t *extended) {
  int is_empty = TRUE;
  for (int i = 0; i < MANTISSA_EXT_BITS; ++i) {
    if (extended[i]) {
      is_empty = FALSE;
    }
  }
  return is_empty;
}
