#include <s21_decimal.h>
void s21_set_bit(s21_decimal *num, unsigned int bit, unsigned int value) {
  if (bit <= MANTISSA_MAX_BIT) {
    if (value == 1) {
      num->bits[bit / BITS_PER_INT] |= (1 << (bit % BITS_PER_INT));
    } else if (value == 0) {
      num->bits[bit / BITS_PER_INT] &= ~(1 << (bit % BITS_PER_INT));
    }
  }
  return;
}
