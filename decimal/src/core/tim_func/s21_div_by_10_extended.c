#include "../arithmetic/arithmetic.h"

int s21_div_by_10_extended(uint32_t *num, uint32_t *last_digit) {
  uint32_t remainder = 0;
  for (int i = 5; i >= 0; --i) {
    uint64_t temp = (uint64_t)num[i] + ((uint64_t)remainder << 32);
    remainder = (uint32_t)(temp % 10);
    num[i] = (uint32_t)(temp / 10);
  }
  *last_digit = remainder;
  return remainder;
}
