#include "s21_decimal.h"

int s21_is_valid_decimal(const s21_decimal *number) {
  uint32_t service_bit = number->bits[BITS_EXP_IDX];
  service_bit &= ~(1U << (BITS_PER_INT - 1));
  uint8_t exp = (service_bit >> BYTE_SHIFT_2) & BYTE_MASK;
  service_bit &= ~(BYTE_MASK << BYTE_SHIFT_2);
  return (service_bit == 0 && exp <= EXP_MAX_VALUE) ? TRUE : FALSE;
}
