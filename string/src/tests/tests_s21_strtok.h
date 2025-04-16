#ifndef TESTS_S21_STRTOK_H
#define TESTS_S21_STRTOK_H

#include "common_header.h"

static int is_equal(const char* str1, const char* str2) {
  return (str1 && str2) ? !strcmp(str1, str2) : (str1 == str2);
}

START_TEST(test_s21_strtok) {
#include "tests_data/strtok_data.h"
  for (s21_size_t i = 0; i < size_strbuff; ++i) {
    for (s21_size_t j = 0; j < size_delimsbuff; ++j) {
      int err = 0;
      char s21_str[256] = {0};
      char orig_str[256] = {0};
      memcpy(s21_str, strbuff[i], strlen(strbuff[i]));
      memcpy(orig_str, strbuff[i], strlen(strbuff[i]));
      char* s21_token = s21_strtok(s21_str, delimsbuff[j]);
      char* orig_token = strtok(orig_str, delimsbuff[j]);
      err = !is_equal(s21_token, orig_token);
      while ((s21_token || orig_token) && !err) {
        s21_token = s21_strtok(NULL, delimsbuff[j]);
        orig_token = strtok(NULL, delimsbuff[j]);
        err = !is_equal(s21_token, orig_token);
      }
      if (err) {
        fprintf(stderr,
                "\n"
                "[  FAILED  ] s21_token test\n"
                "[      IN  ] [%s], [%s]\n"
                "[  EXP     ] %s\n"
                "[     OUT  ] %s\n",
                strbuff[i], delimsbuff[j], orig_token, s21_token);
      }
      ck_assert(!err);
      ++tests_num;
    }
  }
  printf("[  TESTS  ] s21_strtok tests number : %lld\n", tests_num);
}
END_TEST

#endif
