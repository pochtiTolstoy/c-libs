#include <s21_decimal.h>

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_make_decimal_empty(dst);
  int mistake_code = 0;
  if (!dst)
    mistake_code = 1;
  else {
    int64_t abs_src = (src < 0 ? -src : src);
    dst->bits[0] = abs_src;
    s21_set_sign(dst, src >= 0 ? 0 : 1);
  }
  return mistake_code;
}