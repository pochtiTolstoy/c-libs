#ifndef TESTS_S21_TO_LOWER_H
#define TESTS_S21_TO_LOWER_H

#include "common_header.h"
START_TEST(test_s21_to_lower) {
#include "tests_data/to_lower.h"
  for (s21_size_t i = 0; i < count_strings; i++) {
    char *result = (char *)s21_to_lower(input_string[i]);
    ck_assert_str_eq(result, output_string[i]);
    free(result);
    test_num++;
  }

  printf("[  TESTS  ] s21_to_lower tests number : %lld\n", test_num);
}
END_TEST

#endif
