#ifndef TESTS_S21_STRLEN_H
#define TESTS_S21_STRLEN_H

#include "common_header.h"

static char* generate_random_string(s21_size_t bytes) {
  const char lowerbound = 32;
  const char upperbound = 126;
  char* string = (char*)malloc(sizeof(char) * (bytes + 1));
  if (string) {
    for (s21_size_t i = 0; i < bytes; ++i) {
      string[i] = lowerbound + rand() % (upperbound - lowerbound + 1);
    }
    string[bytes] = '\0';
  }
  return string;
}

START_TEST(test_s21_strlen) {
#include "tests_data/strlen_data.h"
  for (s21_size_t i = 0; i < size_stack_buff; ++i) {
    ck_assert_msg(s21_strlen(stack_str_buff[i]) == strlen(stack_str_buff[i]),
                  "[  FAILED  ] s21_strlen test on stack strings");

    tests_num++;
  }

  char* dynamic_str_buff[] = {
      generate_random_string(0), generate_random_string(10),
      generate_random_string(100), generate_random_string(100000)};
  const s21_size_t size_dynamic_buff =
      sizeof(dynamic_str_buff) / sizeof(dynamic_str_buff[0]);

  for (s21_size_t i = 0; i < size_dynamic_buff; ++i) {
    ck_assert_msg(
        s21_strlen(dynamic_str_buff[i]) == strlen(dynamic_str_buff[i]),
        "[ FAILED ] s21_strlen test on random dynamic strings");
    tests_num++;
  }
  for (s21_size_t i = 0; i < size_dynamic_buff; ++i) {
    free(dynamic_str_buff[i]);
  }

  printf("[  TESTS  ] s21_strlen tests number : %lld\n", tests_num);
}
END_TEST

#endif
