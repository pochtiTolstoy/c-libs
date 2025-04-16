
#include "../arithmetic//arithmetic.h"
#include "s21_decimal.h"

void s21_shift_left_extended(const uint32_t *extended, uint32_t *res,
                             size_t shift) {
  memcpy(res, extended, sizeof(*res) * MANTISSA_EXT_BITS);
  for (size_t _ = 0; _ < shift; ++_) {
    uint32_t carry = 0;
    for (size_t cell = 0; cell < MANTISSA_EXT_BITS; ++cell) {
      uint32_t temp = res[cell];
      res[cell] <<= 1;
      res[cell] |= carry;
      carry = (temp >> (BYTE_SHIFT_4 - 1)) & 0x1;
    }
  }
}
