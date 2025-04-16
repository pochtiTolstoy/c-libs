#include "s21_decimal.h"

int s21_is_less(s21_decimal lhs, s21_decimal rhs) {
  s21_big_decimal lhs_big = {0};
  s21_big_decimal rhs_big = {0};
  s21_decimal_to_big_decimal(&lhs, &lhs_big);
  s21_decimal_to_big_decimal(&rhs, &rhs_big);

  int lhs_sign = s21_big_decimal_get_sign(&lhs_big);
  int rhs_sign = s21_big_decimal_get_sign(&rhs_big);

  int result = UNDEFINED;

  if (s21_is_zero(&lhs) && s21_is_zero(&rhs)) {
    result = FALSE;
  } else if (lhs_sign != rhs_sign) {
    result = (lhs_sign == NEG_SIGN) ? TRUE : FALSE;
  } else {
    s21_normalize_big_decimals(&lhs_big, &rhs_big);
    for (int idx = BITS_BIG_DECIMAL_EXP_IDX - 1;
         idx >= 0 && result == UNDEFINED; --idx) {
      if (lhs_big.bits[idx] < rhs_big.bits[idx]) {
        result = TRUE;
      }
      if (lhs_big.bits[idx] > rhs_big.bits[idx]) {
        result = FALSE;
      }
    }
    if (result == UNDEFINED) {
      result = FALSE;
    } else if (lhs_sign != POS_SIGN) {
      result = !result;
    }
  }
  return result;
}
