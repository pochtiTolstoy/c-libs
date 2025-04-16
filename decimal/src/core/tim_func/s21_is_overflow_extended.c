#include "../arithmetic//arithmetic.h"

int s21_is_overflow_extended(const uint32_t *extended) {
  return (extended[5] || extended[4] || extended[3]);
}
