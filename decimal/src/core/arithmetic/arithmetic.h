#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <stdint.h>
#include <stdlib.h>

#include "s21_decimal.h"

void s21_bank_rounding(uint32_t *extended, uint32_t last_digit_);
int s21_add_mantissa(const uint32_t *lhs, const uint32_t *rhs, uint32_t *res);
int s21_is_overflow_extended(const uint32_t *extended);
void s21_div_maximized_extended(uint32_t *lhs, const uint32_t *rhs,
                                uint32_t *rem);
int s21_get_msb_pos(const uint32_t *extended);
void s21_shift_left_extended(const uint32_t *extended, uint32_t *res,
                             size_t shift);
int s21_is_equal_extended(const uint32_t *rhs, const uint32_t *lhs);
int s21_is_less_or_equal_extended(const uint32_t *lhs, const uint32_t *rhs);
int s21_is_less_extended(const uint32_t *lhs, const uint32_t *rhs);
void s21_sub_extended(uint32_t *lhs, const uint32_t *rhs);
void s21_add_extended(uint32_t *lhs, const uint32_t *rhs);
int s21_div_by_10_extended(uint32_t *num, uint32_t *last_digit);
void s21_remove_trailing_zeros(s21_decimal *value);

#endif
