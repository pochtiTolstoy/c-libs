#ifndef TESTS_S21_STRNCAT_H
#define TESTS_S21_STRNCAT_H

#include "common_header.h"

START_TEST(test_s21_strncat) {
#include "tests_data/strncat_data.h"
  for (s21_size_t i = 0; i < size_destbuff; ++i) {
    for (s21_size_t j = 0; j < size_srcbuff; ++j) {
      for (s21_size_t k = 0; k < size_lenbuff; k++) {
        char s21_res[128] = {0};
        char orig_res[128] = {0};
        memcpy(s21_res, destbuff[i], strlen(destbuff[i]));
        memcpy(orig_res, destbuff[i], strlen(destbuff[i]));
        s21_strncat(s21_res, srcbuff[j], lenbuff[k]);
        strncat(orig_res, srcbuff[j], lenbuff[k]);
        int res = (strcmp(s21_res, orig_res) == 0);
        if (!res) {
          fprintf(stderr,
                  "\n"
                  "[  FAILED  ] s21_strncat test\n"
                  "[      IN  ] [%s], [%s], [%llu]\n"
                  "[  EXP     ] %s\n"
                  "[     OUT  ] %s\n\n",
                  destbuff[i], srcbuff[j], lenbuff[j], orig_res, s21_res);
        }
        ck_assert(res);
        tests_num++;
      }
    }
  }
  printf("[  TESTS  ] s21_strncat tests number : %llu\n", tests_num);
}
END_TEST

#endif
