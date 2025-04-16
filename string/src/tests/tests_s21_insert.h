#ifndef TESTS_S21_INSERT_H
#define TESTS_S21_INSERT_H

#include "common_header.h"
START_TEST(test_s21_insert) {
#include "tests_data/insert.h"
  for (s21_size_t i = 0; i < count_strings; i++) {
    char *result = (char *)s21_insert(input_string1[i], input_string2[i],
                                      insert_indices[i]);
    ck_assert_str_eq(result, output_string[i]);
    free(result);
    test_num++;
  }

  printf("[  TESTS  ] s21_insert tests number : %lld\n", test_num);
}
END_TEST

#endif
