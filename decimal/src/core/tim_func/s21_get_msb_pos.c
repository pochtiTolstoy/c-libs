#include "../arithmetic/arithmetic.h"
#include "s21_decimal.h"

int s21_get_msb_pos(const uint32_t *extended) {
  int bits = MANTISSA_EXT_BITS * BITS_PER_INT;
  int msb_pos = 0;
  for (int pos = 0; pos < bits; ++pos) {
    if ((extended[pos / BITS_PER_INT] >> (pos % BITS_PER_INT)) & 0x1) {
      msb_pos = pos;
    }
  }
  return msb_pos;
}
