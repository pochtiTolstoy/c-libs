#include <s21_decimal.h>

void s21_make_decimal_empty(s21_decimal *num) {
  if (num) {
    num->bits[0] = 0;
    num->bits[1] = 0;
    num->bits[2] = 0;
    num->bits[3] = 0;
  }
}
