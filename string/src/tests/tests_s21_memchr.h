#ifndef TESTS_S21_MEMCHR_H
#define TESTS_S21_MEMCHR_H
#include "common_header.h"

START_TEST(test_s21_memchr) {
#include "tests_data/memchr_data.h"
  for (s21_size_t i = 0; i < size_srcbuff; ++i) {
    for (s21_size_t j = 0; j < size_symbbuff; ++j) {
      for (s21_size_t k = 0; k < size_nbuff; ++k) {
        const void* orig_res = memchr(srcbuff[i], symbbuff[j], nbuff[k]);
        void* s21_res = s21_memchr(srcbuff[i], symbbuff[j], nbuff[k]);
        int result = (s21_res == orig_res);
        if (!result) {
          fprintf(stderr,
                  "\n"
                  "[  FAILED  ] s21_memchr test\n"
                  "[      IN  ] [%s], [%c], [%llu]\n"
                  "[  EXP     ] %p\n"
                  "[     OUT  ] %p\n"
                  "[  DIFF    ] %lu\n\n",
                  srcbuff[i], symbbuff[j], nbuff[k], orig_res, s21_res,
                  (unsigned char*)orig_res - (unsigned char*)s21_res);
        }
        ck_assert(result);
        tests_num++;
      }
    }
  }
  printf("[  TESTS  ] s21_memchr tests number : %llu\n", tests_num);
}
END_TEST

#endif
