#include <s21_decimal.h>
int s21_get_op_sign_plus_minus(int sign_num1, int sign_num2, int op_sign,
                               int index_greatest) {
  return (index_greatest == 1 ? sign_num1 : (sign_num2 + op_sign) % 2);
}
