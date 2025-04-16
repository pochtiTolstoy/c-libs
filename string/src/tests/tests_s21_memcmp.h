#ifndef TESTS_S21_MEMCMP_H
#define TESTS_S21_MEMCMP_H
#include "common_header.h"

START_TEST(test_s21_memcmp) {
#include "tests_data/memcmp_data.h"
  for (s21_size_t i = 0; i < size_ar1; i++) {
    for (s21_size_t j = 0; j < size_ar2; j++) {
      for (s21_size_t k = 0; k < size_ar3; k++) {
        int s21_res = s21_memcmp(array1[i], array2[j], array3[k]);
        int orig_res = memcmp(array1[i], array2[j], array3[k]);
        int result =
            ((s21_res > 0 && orig_res > 0) || (s21_res < 0 && orig_res < 0) ||
             (s21_res == 0 && orig_res == 0));
        if (!result) {
          fprintf(stderr,
                  "\n"
                  "[  FAILED  ] s21_memcmp test\n"
                  "[      IN  ] [%s], [%s]\n"
                  "[  EXP     ] %d\n"
                  "[     OUT  ] %d\n\n",
                  array1[i], array2[i], orig_res, s21_res);
        }
        ck_assert(result);
        tests_num++;
      }
    }
  }
  printf("[  TESTS  ] s21_memcmp tests number : %llu\n", tests_num);
}
END_TEST

#endif
