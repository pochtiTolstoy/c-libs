#include "../arithmetic/arithmetic.h"

int s21_is_less_or_equal_extended(const uint32_t *lhs, const uint32_t *rhs) {
  return s21_is_equal_extended(lhs, rhs) || s21_is_less_extended(lhs, rhs);
}
