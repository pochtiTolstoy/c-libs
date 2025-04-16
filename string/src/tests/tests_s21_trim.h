#ifndef TESTS_S21_TRIM_H
#define TESTS_S21_TRIM_H

#include "common_header.h"
START_TEST(test_s21_trim) {
#include "tests_data/trim.h"
  for (s21_size_t i = 0; i < count_strings; i++) {
    char *result = (char *)s21_trim(input_string[i], trim_chars[i]);
    ck_assert_str_eq(result, output_string[i]);
    free(result);
    test_num++;
  }

  printf("[  TESTS  ] s21_trim tests number : %lld\n", test_num);
}
END_TEST

#endif
