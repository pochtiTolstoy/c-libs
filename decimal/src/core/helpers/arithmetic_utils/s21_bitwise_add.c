#include <s21_decimal.h>

void s21_bitwise_add(const s21_big_decimal* num1, const s21_big_decimal* num2,
                     s21_big_decimal* result) {
  unsigned int mem = 0;
  for (int i = 0; i <= MANTISSA_MAX_BIT_BIG_DECIMAL; i++) {
    int sum =
        s21_big_decimal_get_bit(num1, i) + s21_big_decimal_get_bit(num2, i);
    sum += mem;
    s21_big_decimal_set_bit(result, i, sum % 2);
    mem = sum / 2;
  }
  s21_big_decimal_set_scale(result, s21_big_decimal_get_scale(num1));
}