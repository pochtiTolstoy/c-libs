#ifndef TESTS_S21_STRCSPN_H
#define TESTS_S21_STRCSPN_H
#include "common_header.h"

START_TEST(test_s21_strcspn) {
#include "tests_data/strcspn_data.h"
  for (s21_size_t i = 0; i < size_source; ++i) {
    for (s21_size_t j = 0; j < size_template; ++j) {
      s21_size_t s21_res = s21_strcspn(source_buff[i], template_buff[j]);
      s21_size_t orig_res = strcspn(source_buff[i], template_buff[j]);
      int result = (s21_res == orig_res);
      tests_num++;
      if (!result) {
        fprintf(stderr,
                "\n"
                "[  FAILED  ] s21_strcspn test\n"
                "[      IN  ] [%s], [%s]\n"
                "[  EXP     ] %llu\n"
                "[     OUT  ] %llu\n\n",
                source_buff[i], template_buff[j], orig_res, s21_res);
      }
      ck_assert(result);
    }
  }
  printf("[  TESTS  ] s21_strcspn tests number : %llu\n", tests_num);
}
END_TEST

#endif
