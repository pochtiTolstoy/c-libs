#include "../arithmetic/arithmetic.h"
#include "s21_decimal.h"

void s21_div_maximized_extended(uint32_t *lhs, const uint32_t *rhs,
                                uint32_t *rem) {
  uint32_t lhs_reduced[MANTISSA_EXT_BITS] = {0};
  uint32_t rhs_shifted[MANTISSA_EXT_BITS] = {0};
  uint32_t exp_value[MANTISSA_EXT_BITS] = {0};
  uint32_t division_result[MANTISSA_EXT_BITS] = {0};
  const uint32_t zero_value[MANTISSA_EXT_BITS] = {0};
  const uint32_t one_value[MANTISSA_EXT_BITS] = {1};
  memcpy(lhs_reduced, lhs, sizeof(lhs_reduced));
  memcpy(rhs_shifted, rhs, sizeof(rhs_shifted));
  int bits_alignment = s21_get_msb_pos(lhs) - s21_get_msb_pos(rhs);
  for (int bits_shift = bits_alignment; bits_shift >= 0; --bits_shift) {
    s21_shift_left_extended(rhs, rhs_shifted, (size_t)bits_shift);
    int is_zero = s21_is_equal_extended(rhs_shifted, zero_value);
    if (!is_zero && s21_is_less_or_equal_extended(rhs_shifted, lhs_reduced)) {
      s21_sub_extended(lhs_reduced, rhs_shifted);
      s21_shift_left_extended(one_value, exp_value, bits_shift);
      s21_add_extended(division_result, exp_value);
    }
  }
  memcpy(lhs, division_result, sizeof(division_result));
  memcpy(rem, lhs_reduced, sizeof(lhs_reduced));
}
