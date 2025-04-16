#include <s21_decimal.h>

int s21_get_bit(const s21_decimal *num, int bit) {
  return (num->bits[bit / BITS_PER_INT] & (1 << (bit % BITS_PER_INT))) != 0 ? 1
                                                                            : 0;
}
