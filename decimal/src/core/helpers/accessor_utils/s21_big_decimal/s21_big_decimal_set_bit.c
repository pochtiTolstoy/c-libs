#include <s21_decimal.h>

void s21_big_decimal_set_bit(s21_big_decimal *num, unsigned int bit,
                             unsigned int value) {
  if (bit <= MANTISSA_MAX_BIT_BIG_DECIMAL) {
    if (value == 1) {
      num->bits[bit / BITS_PER_INT] |= (1 << (bit % BITS_PER_INT));
    } else if (value == 0) {
      num->bits[bit / BITS_PER_INT] &= ~(1 << (bit % BITS_PER_INT));
    }
  }
}