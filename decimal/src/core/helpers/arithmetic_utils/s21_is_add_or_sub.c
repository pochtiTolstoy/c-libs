#include <s21_decimal.h>

int s21_is_add_or_sub(int sign_num1, int sign_num2, int op_sign) {
  return !(((sign_num1 == sign_num2) && op_sign == POS_SIGN) ||
           ((sign_num1 != sign_num2) && op_sign == NEG_SIGN));
}