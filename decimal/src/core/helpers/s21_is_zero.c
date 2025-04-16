#include <s21_decimal.h>

int s21_is_zero(const s21_decimal *num) {
  return num->bits[0] == 0 && num->bits[1] == 0 && num->bits[2] == 0;
}
