#include "../arithmetic/arithmetic.h"
#include "s21_decimal.h"

void s21_bank_rounding(uint32_t *extended, uint32_t last_digit_) {
  int round = FALSE;
  int last_extended_bit = (*extended) & 0x1;
  s21_decimal last_digit = {{last_digit_, 0, 0, 0}};
  s21_decimal five_value = {{5, 0, 0, 0}};
  if (s21_is_greater(last_digit, five_value)) {
    round = TRUE;
  } else if (s21_is_equal(last_digit, five_value) && last_extended_bit) {
    round = TRUE;
  }
  if (round == TRUE) {
    uint32_t rhs[MANTISSA_EXT_BITS] = {1};
    uint32_t lhs[MANTISSA_EXT_BITS];
    memcpy(lhs, extended, sizeof(lhs));
    s21_add_mantissa(lhs, rhs, extended);
  }
}
